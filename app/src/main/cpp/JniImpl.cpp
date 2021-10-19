
#include <jni.h>
#include <string>
#include "ITRTCCloud.h"
#include "util/LogUtil.h"
#include "TRTCCloudCore.h"
using namespace liteav;

TRTCCloudCore * trtcCloudCore= nullptr;


void checkTRTC(JNIEnv *env){
    if (trtcCloudCore== nullptr){
        trtcCloudCore=TRTCCloudCore::GetInstance(env);
    }

}

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
Java_com_project_trtcndkdemo_naviteUtils_TRTCNativeManager_getSDKVersion(JNIEnv *env, jclass clazz) {
    // TODO: implement getSDKVersion()
    checkTRTC(env);
    return env->NewStringUTF(liteav::ITRTCCloud::getTRTCShareInstance(nullptr)->getSDKVersion());
}

JNIEXPORT void JNICALL
Java_com_project_trtcndkdemo_naviteUtils_TRTCNativeManager_nativeStartLocalVideo(JNIEnv *env, jclass clazz,
                                                                     jboolean front_camera,
                                                                     jobject view) {
    // TODO: implement nativeStartLocalVideo()
    checkTRTC(env);
    trtcCloudCore->getTRTCCloud()->startLocalPreview(front_camera,view);

}
JNIEXPORT void JNICALL
Java_com_project_trtcndkdemo_naviteUtils_TRTCNativeManager_startLocalAudio(JNIEnv *env, jclass clazz) {
    // TODO: implement startLocalAudio()
    checkTRTC(env);
    trtcCloudCore->getTRTCCloud()->startLocalAudio(TRTCAudioQualityDefault);

}
JNIEXPORT void JNICALL
Java_com_project_trtcndkdemo_naviteUtils_TRTCNativeManager_enterRoom(JNIEnv *env, jclass clazz, jstring room_id,
                                                         jstring user_id, jstring user_sig,
                                                         jint sdk_app_id) {
    // TODO: implement enterRoom()
    checkTRTC(env);
   const char *strRoomId=env->GetStringUTFChars(room_id, nullptr);
   const char *userId=env->GetStringUTFChars(user_id, nullptr);
   const char *userSig=env->GetStringUTFChars(user_sig, nullptr);


    TRTCParams trtcParams;
    trtcParams.role=TRTCRoleAnchor;
    trtcParams.strRoomId=strRoomId;
    trtcParams.userId=userId;
    trtcParams.sdkAppId=sdk_app_id;
    trtcParams.userSig=userSig;
    trtcCloudCore->getTRTCCloud()->enterRoom(trtcParams,TRTCAppSceneVideoCall);
    trtcCloudCore->InitCallBack();

    env->ReleaseStringUTFChars(room_id,strRoomId);
    env->ReleaseStringUTFChars(user_id,userId);
    env->ReleaseStringUTFChars(user_sig,userSig);


}
JNIEXPORT void JNICALL
Java_com_project_trtcndkdemo_naviteUtils_TRTCNativeManager_nativeDestroy(JNIEnv *env,
                                                                         jclass clazz) {
    checkTRTC(env);
    // TODO: implement nativeDestory()
    trtcCloudCore->UninitCallBack();
    trtcCloudCore->PreUninit();
    TRTCCloudCore::Destory();
    trtcCloudCore= nullptr;

}
JNIEXPORT void JNICALL
Java_com_project_trtcndkdemo_naviteUtils_TRTCNativeManager_nativeStartRemoteView(JNIEnv *env,
                                                                                 jclass clazz,
                                                                                 jstring user_id,
                                                                                 jint stream_type,
                                                                                 jobject view) {
    // TODO: implement nativeStartRemoteView()
    checkTRTC(env);
    const char *userID=env->GetStringUTFChars(user_id, nullptr);

    trtcCloudCore->getTRTCCloud()->startRemoteView(userID, (trtc::TRTCVideoStreamType)stream_type,view);

    env->ReleaseStringUTFChars(user_id,userID);

}
#ifdef __cplusplus
}
#endif

