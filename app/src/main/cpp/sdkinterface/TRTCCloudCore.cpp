//
// Created by Sumn on 2021/10/13.
//
#include <jni.h>
#include "TRTCCloudCore.h"
#include "LogUtil.h"

TRTCCloudCore *TRTCCloudCore::m_instance = nullptr;



TRTCCloudCore *TRTCCloudCore::GetInstance(JNIEnv *env) {
        if (m_instance == nullptr) {
            m_instance = new TRTCCloudCore(env);



        }
    return m_instance;
}

void TRTCCloudCore::Destory() {

    if (m_instance) {
        delete m_instance;
        m_instance = nullptr;
    }

}

TRTCCloudCore::TRTCCloudCore(JNIEnv *env) {
    m_pCloud = getTRTCShareInstance(nullptr);
    m_pDeviceManager = getTRTCShareInstance(nullptr)->getDeviceManager();
    m_env=env;
}

TRTCCloudCore::~TRTCCloudCore() {
    LOGCATE("destroy");
    destroyTRTCShareInstance();
    m_pCloud = nullptr;
    m_env= nullptr;


}

void TRTCCloudCore::InitCallBack() {
    m_pCloud->addCallback(this);
}

void TRTCCloudCore::UninitCallBack() {
    m_pCloud->removeCallback(this);

}

void TRTCCloudCore::PreUninit() {
    m_bPreUninit = true;
    m_pCloud->stopAllRemoteView();
    m_pCloud->stopLocalPreview();
    m_pCloud->stopLocalAudio();
    m_pCloud->exitRoom();

}

ITRTCCloud *TRTCCloudCore::getTRTCCloud() {
    return m_pCloud;
}

ITXDeviceManager *TRTCCloudCore::getDeviceManager() {
    return m_pDeviceManager;
}

ITRTCCloudCallback *TRTCCloudCore::GetITRTCCloudCallback() {
    return this;
}

void TRTCCloudCore::onError(TXLiteAVError errCode, const char *errMsg, void *arg) {
    LOGCATE("onError errorCode[%d], errorInfo[%s]\n", errCode, errMsg);

}

void TRTCCloudCore::onWarning(TXLiteAVWarning warningCode, const char *warningMsg, void *arg) {
    LOGCATE("onWarning errorCode[%d], errorInfo[%s]\n", warningCode, warningMsg);


}

void TRTCCloudCore::onEnterRoom(int result) {

    LOGCATI("onEnterRoom elapsed[%d]\n", result);
}

void TRTCCloudCore::onExitRoom(int reason) {
    LOGCATI("onExitRoom reason[%d]\n", reason);


}

void TRTCCloudCore::onRemoteUserEnterRoom(const char *userId) {
    LOGCATI("onMemberEnter userId[%s]\n", userId);

}

void TRTCCloudCore::onRemoteUserLeaveRoom(const char *userId, int reason) {
    LOGCATI("onMemberExit userId[%s]\n", userId);

}

void TRTCCloudCore::onUserAudioAvailable(const char *userId, bool available) {
    LOGCATI("onUserAudioAvailable userId[%s] available[%d]\n", userId, available);

}

void TRTCCloudCore::onSwitchRoom(TXLiteAVError errCode, const char *errMsg) {
    LOGCATI("onSwitchRoom errorCode[%d], errorInfo[%s]\n", errCode, errMsg);

}

void TRTCCloudCore::onFirstAudioFrame(const char *userId) {
    LOGCATI("onFirstAudioFrame userId[%s] \n", userId);

}

void TRTCCloudCore::onUserSubStreamAvailable(const char *userId, bool available) {
    LOGCATI("onUserSubStreamAvailable userId[%s] available[%d]\n", userId, available);

}

void TRTCCloudCore::onUserVideoAvailable(const char *userId, bool available) {
    LOGCATI("onUserVideoAvailable userId[%s] available[%d]\n", userId, available);
    jclass  clazz=m_env->FindClass("com/project/trtcndkdemo/naviteUtils/JniCallBack");
    jmethodID videoAvailable=m_env->GetStaticMethodID(clazz,"jniCallUserVideoAvailable","(Ljava/lang/String;Z)V");
    jstring jUser=m_env->NewStringUTF(userId);
    jboolean jAvailable=available;
    m_env->CallStaticVoidMethod(clazz,videoAvailable,jUser,jAvailable);




}

void TRTCCloudCore::onCameraDidReady() {
    LOGCATI("onCameraDidReady");
}

void TRTCCloudCore::onMicDidReady() {
    LOGCATI("onMicDidReady");
}

void TRTCCloudCore::onConnectionRecovery() {
    LOGCATI("onConnectionRecovery");
}

void TRTCCloudCore::onTryToReconnect() {
    LOGCATI("onTryToReconnect");
}

void TRTCCloudCore::onConnectionLost() {
    LOGCATI("onConnectionLost");
}

void TRTCCloudCore::onNetworkQuality(TRTCQualityInfo localQuality, TRTCQualityInfo *remoteQuality,
                                     uint32_t remoteQualityCount) {

}

void TRTCCloudCore::onStatistics(const TRTCStatistics &statis) {

}

void TRTCCloudCore::onUserVoiceVolume(TRTCVolumeInfo *userVolumes, uint32_t userVolumesCount,
                                      uint32_t totalVolume) {

}

