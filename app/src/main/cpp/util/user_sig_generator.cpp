// Copyright (c) 2020 Tencent. All rights reserved.

#include "user_sig_generator.h"

#include <sys/select.h>
#include <algorithm>
#include <cstring>
#include <memory>
#include <string>

#include "base64.h"
#include "evp.h"
#include "hmac.h"
#include <zlib.h>
#include <digest.h>

namespace liteav {
    namespace {



        std::string Hmacsha256(uint32_t sdk_app_id,
                               const std::string &user_id,
                               const std::string &key,
                               uint32_t curr_time,
                               uint32_t expire_time) {
            // 拼接计算TLS.sig需要的字符串，除|user_id|外
            // 为其他字符预留256字节空间，此预留值与trtc c++ demo
            // 保持一致
            const int32_t data_buffer_len = user_id.size() + 256;

            // 拼接规定格式的字符串
            std::unique_ptr<char[]> data_buffer(new char[data_buffer_len]);
            const int count =
                    snprintf(data_buffer.get(), data_buffer_len,
                             "TLS.identifier:%s\n"
                             "TLS.sdkappid:%u\n"
                             "TLS.time:%u\n"
                             "TLS.expire:%u\n",
                             user_id.c_str(), sdk_app_id, curr_time, expire_time);
            if (count < 0) {
                return "";
            }

            // 使用hmac-sha256算法计算摘要,|hmac_out_len|为计算后的摘要字节数
            uint8_t hmac_out[EVP_MAX_MD_SIZE];
            uint32_t hmac_out_len = 0;
            uint8_t *hmac_res =
                    HMAC(EVP_sha256(), static_cast<const void *>(key.c_str()), key.length(),
                         reinterpret_cast<const uint8_t *>(data_buffer.get()), count, hmac_out,
                         &hmac_out_len);
            if (hmac_res == nullptr) {
                return "";
            }

            // base64编码,获取编码后的字节数
            size_t base64_buffer_len = 0;
            if (!EVP_EncodedLength(&base64_buffer_len, hmac_out_len)) {
            }
            // base64编码
            std::unique_ptr<uint8_t[]> base64_buffer(new uint8_t[base64_buffer_len]);
            int byte_write = EVP_EncodeBlock(base64_buffer.get(), hmac_out, hmac_out_len);
            if (byte_write < 0) {
                // LOG(ERROR) << "base64 encode failed with EVP_EncodeBlock";
                return "";
            }
            return std::string(reinterpret_cast<char *>(base64_buffer.get()), byte_write);
        }
    }  // namespace

    bool GenerateUserSig(uint32_t sdk_app_id,
                         const char *key,
                         const char *user_id,
                         char *user_sig,
                         size_t *user_sig_size,
                         int expired_in_seconds) {
        struct timeval time;
        gettimeofday(&time, nullptr);
        uint32_t curr_time = static_cast<uint32_t>(time.tv_sec);
        // 获得了|expire_time|对应的秒数
        uint32_t uint_expire_time = static_cast<uint32_t>(expired_in_seconds);

        std::string _user_id = user_id;
        std::string _key = key;
        // 使用hmacsha256算法计算TLS.sig字段
        std::string sig =
                Hmacsha256(sdk_app_id, _user_id, _key, curr_time, uint_expire_time);
        if (sig == "") {
            // LOG(ERROR) << "get TLS.sig failed when using hmacsha256 function";
            return false;
        }

        // 除TLS.sig外，为其他json字符预留256字节空间,预留空间大小与trtc c++ demo
        // 保持一致
        const int32_t data_buffer_len = sig.length() + 256;
        std::unique_ptr<char[]> data_buffer(new char[data_buffer_len]);
        // 拼接json格式的字符串
        const int32_t count = std::snprintf(data_buffer.get(), data_buffer_len,
                                            "{"
                                            "\"TLS.ver\":\"2.0\","
                                            "\"TLS.identifier\":\"%s\","
                                            "\"TLS.sdkappid\":%u,"
                                            "\"TLS.expire\":%u,"
                                            "\"TLS.time\":%u,"
                                            "\"TLS.sig\":\"%s\""
                                            "}",
                                            _user_id.c_str(), sdk_app_id,
                                            uint_expire_time, curr_time, sig.c_str());
        if (count < 0) {
            // LOG(ERROR) << "get json format TLS string failed";
            return false;
        }

        // zlib进行压缩,|zip_dest_len|为压缩后的字节数
        std::unique_ptr<Bytef[]> zip_dest(new Bytef[count]);
        uLongf zip_dest_len = count;
        int zip_res = compress2(zip_dest.get(), &zip_dest_len,
                                reinterpret_cast<const Bytef *>(data_buffer.get()),
                                count, Z_BEST_SPEED);
        if (zip_res != Z_OK) {
            // LOG(ERROR) << "compress failed with zlib";
            return false;
        }

        // base64编码,获取编码后的字节数
        // base64编码将三个字节共24位分配到新的4个字节，每个字节各6位
        // 添加结尾NUL,base64编码后字节数为base64_len = ((len - 1)/3 + 1) * 4 + 1
        size_t base64_buffer_len = 0;
        if (!EVP_EncodedLength(&base64_buffer_len, zip_dest_len)) {
            // LOG(ERROR) << "get base64 encoded buffer length failed";
        }
        // 对压缩后的数据进行base64编码
        std::unique_ptr<uint8_t[]> base64_buffer(new uint8_t[base64_buffer_len]);
        int byte_write = EVP_EncodeBlock(
                base64_buffer.get(), reinterpret_cast<const uint8_t *>(zip_dest.get()),
                zip_dest_len);
        if (byte_write < 0) {
            // LOG(ERROR) << "base64 encode failed with EVP_EncodeBlock";
            return false;
        }

        // 在base64编码的基础上添加一些加密操作
        std::string result(reinterpret_cast<const char *>(base64_buffer.get()),
                           byte_write);
        std::replace(result.begin(), result.end(), '+', '*');
        std::replace(result.begin(), result.end(), '/', '-');
        std::replace(result.begin(), result.end(), '=', '_');

        if (*user_sig_size <= result.size()) {
            return false;
        } else {
            memcpy(user_sig, result.c_str(), result.size());
            *user_sig_size = result.size();
        }

        return true;
    };
} // namespace liteav
