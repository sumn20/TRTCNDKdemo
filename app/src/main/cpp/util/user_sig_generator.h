// Copyright (c) 2021 Tencent. All rights reserved.

#ifndef SDK_SERVER_SAMPLE_SIG_GEN_USER_SIG_GENERATOR_H_
#define SDK_SERVER_SAMPLE_SIG_GEN_USER_SIG_GENERATOR_H_

#include <unistd.h>
#include <cstddef>
#include <stdint.h>

namespace liteav {

#if defined(_WIN32)

#if defined(NOT_BUILD_TRTC_SDK)
#define TRTC_API
#else
#if defined(BUILD_TRTC_SDK)
#define TRTC_API __declspec(dllexport)
#else
#define TRTC_API __declspec(dllimport)
#endif  // defined(BUILD_TRTC_SDK)
#endif

#else  // defined(_WIN32)
#if defined(BUILD_TRTC_SDK)
#define TRTC_API __attribute__((visibility("default")))
#else
#define TRTC_API
#endif
#endif
    const char kSdkDemoKey[] =
            "";
    const int SDKAPPID = 0;
// 功能：生成用户签名，默认有效期为7天
// |sdk_app_id| - 应用 ID
// |key| - 应用 Key，‘\0’ 结尾 c 风格字符串
// |user_id| - 用户 ID， ‘\0’ 结尾 c 风格字符串
// |user_sig| - 生成的签名
// |user_sig_size| - 生成的签名的长度，作为入参表示 |user_sig| 的容量
// |expried_in_seconds| - 签名有效期，从生成开始算
//
// 返回值
// - true : 成功
// - false : 失败
bool TRTC_API GenerateUserSig(uint32_t sdk_app_id,
                              const char* key,
                              const char* user_id,
                              char* user_sig,
                              size_t* user_sig_size,
                              int expired_in_seconds = 7 * 3600 * 24);

}  // namespace liteav

#endif  // SDK_SERVER_SAMPLE_SIG_GEN_USER_SIG_GENERATOR_H_
