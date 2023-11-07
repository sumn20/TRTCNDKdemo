//
// Created by Sumn on 2021/10/13.
//

#ifndef TRTCNDKDEMO_TRTCCLOUDCORE_H
#define TRTCNDKDEMO_TRTCCLOUDCORE_H
#include "ITRTCCloud.h"
#include "LogUtil.h"
using  namespace liteav;

class TRTCCloudCore : public ITRTCCloudCallback,ITRTCVideoRenderCallback{
public:
    static TRTCCloudCore* GetInstance(JNIEnv *env);
    static void Destory();
    TRTCCloudCore(JNIEnv *m_env);
    ~TRTCCloudCore();

public:
    void InitCallBack();
    void UninitCallBack();
    void PreUninit();
    ITRTCCloud * getTRTCCloud();
    ITXDeviceManager * getDeviceManager();
    ITRTCCloudCallback* GetITRTCCloudCallback();



public:
    //interface ITRTCCloudCallback
    virtual void onError(TXLiteAVError errCode, const char* errMsg, void* arg);
    virtual void onWarning(TXLiteAVWarning warningCode, const char* warningMsg, void* arg);
    virtual void onEnterRoom(int result);
    virtual void onExitRoom(int reason);
    virtual void onRemoteUserEnterRoom(const char* userId);
    virtual void onRemoteUserLeaveRoom(const char* userId, int reason);
    virtual void onUserAudioAvailable(const char* userId, bool available);
    virtual void onSwitchRoom(TXLiteAVError errCode, const char* errMsg);
    virtual void onFirstAudioFrame(const char* userId);
    virtual void onUserVoiceVolume(TRTCVolumeInfo* userVolumes, uint32_t userVolumesCount, uint32_t totalVolume);
    virtual void onUserSubStreamAvailable(const char* userId, bool available);
    virtual void onUserVideoAvailable(const char* userId, bool available);
    virtual void onNetworkQuality(TRTCQualityInfo localQuality, TRTCQualityInfo* remoteQuality, uint32_t remoteQualityCount);
    virtual void onStatistics(const TRTCStatistics& statis);
    virtual void onConnectionLost();
    virtual void onTryToReconnect();
    virtual void onConnectionRecovery();
    //设备相关接口回调
    virtual void onCameraDidReady();

    virtual void onMicDidReady();
    virtual void onFirstVideoFrame(const char* userId, const TRTCVideoStreamType streamType, const int width, const int height);
    virtual void onRenderVideoFrame(const char* userId, TRTCVideoStreamType streamType, TRTCVideoFrame* frame) ;
private:
    static TRTCCloudCore* m_instance;
    ITRTCCloud* m_pCloud = nullptr;
    ITXDeviceManager* m_pDeviceManager = nullptr;
    bool m_bPreUninit = false;
    JNIEnv *m_env;


};


#endif //TRTCNDKDEMO_TRTCCLOUDCORE_H
