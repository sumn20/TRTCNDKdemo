
#include <jni.h>
#include <string>
#include "ITRTCCloud.h"
#include "util/LogUtil.h"
#include "TRTCCloudCore.h"
#include "user_sig_generator.h"

using namespace liteav;

TRTCCloudCore *trtcCloudCore = nullptr;


void checkTRTC(JNIEnv *env) {
    if (trtcCloudCore == nullptr) {
        trtcCloudCore = TRTCCloudCore::GetInstance(env);
    }

}

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
Java_com_project_trtcndkdemo_naviteUtils_TRTCNativeManager_getSDKVersion(JNIEnv *env,
                                                                         jclass clazz) {
    // TODO: implement getSDKVersion()
    checkTRTC(env);
    return env->NewStringUTF(liteav::ITRTCCloud::getTRTCShareInstance(nullptr)->getSDKVersion());
}

JNIEXPORT void JNICALL
Java_com_project_trtcndkdemo_naviteUtils_TRTCNativeManager_nativeStartLocalVideo(JNIEnv *env,
                                                                                 jclass clazz,
                                                                                 jboolean front_camera,
                                                                                 jobject view) {
    // TODO: implement nativeStartLocalVideo()
    checkTRTC(env);
    trtcCloudCore->getTRTCCloud()->startLocalPreview(front_camera, view);

}
JNIEXPORT void JNICALL
Java_com_project_trtcndkdemo_naviteUtils_TRTCNativeManager_startLocalAudio(JNIEnv *env,
                                                                           jclass clazz) {
    // TODO: implement startLocalAudio()
    checkTRTC(env);
    trtcCloudCore->getTRTCCloud()->startLocalAudio(TRTCAudioQualityDefault);

}
JNIEXPORT void JNICALL
Java_com_project_trtcndkdemo_naviteUtils_TRTCNativeManager_enterRoom(JNIEnv *env, jclass clazz,
                                                                     jstring room_id,
                                                                     jstring user_id) {
    // TODO: implement enterRoom()
    checkTRTC(env);
    const char *strRoomId = env->GetStringUTFChars(room_id, nullptr);
    const char *userId = env->GetStringUTFChars(user_id, nullptr);


    TRTCParams trtcParams;
    trtcParams.role = TRTCRoleAnchor;
    trtcParams.strRoomId = strRoomId;
    trtcParams.userId = userId;
    trtcParams.sdkAppId = SDKAPPID;
    char sig[1024] = {0};
    size_t sig_size = 1024;
    GenerateUserSig(SDKAPPID, kSdkDemoKey, userId, sig, &sig_size);
    trtcParams.userSig = sig;
    trtcCloudCore->getTRTCCloud()->enterRoom(trtcParams, TRTCAppSceneVideoCall);
    trtcCloudCore->InitCallBack();

    env->ReleaseStringUTFChars(room_id, strRoomId);
    env->ReleaseStringUTFChars(user_id, userId);


}
JNIEXPORT void JNICALL
Java_com_project_trtcndkdemo_naviteUtils_TRTCNativeManager_nativeDestroy(JNIEnv *env,
                                                                         jclass clazz) {
    checkTRTC(env);
    // TODO: implement nativeDestory()
    trtcCloudCore->UninitCallBack();
    trtcCloudCore->PreUninit();
    TRTCCloudCore::Destory();
    trtcCloudCore = nullptr;

}
JNIEXPORT void JNICALL
Java_com_project_trtcndkdemo_naviteUtils_TRTCNativeManager_nativeStartRemoteView(JNIEnv *env,
                                                                                 jclass clazz,
                                                                                 jstring user_id,
                                                                                 jint stream_type,
                                                                                 jobject view) {
    // TODO: implement nativeStartRemoteView()
    checkTRTC(env);
    const char *userID = env->GetStringUTFChars(user_id, nullptr);

    trtcCloudCore->getTRTCCloud()->startRemoteView(userID, (trtc::TRTCVideoStreamType) stream_type,
                                                   view);
    env->ReleaseStringUTFChars(user_id, userID);

}
#ifdef __cplusplus
}
#endif

