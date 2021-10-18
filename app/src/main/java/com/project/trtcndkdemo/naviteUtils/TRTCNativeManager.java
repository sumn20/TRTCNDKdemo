package com.project.trtcndkdemo.naviteUtils;



import com.tencent.rtmp.ui.TXCloudVideoView;

public class TRTCNativeManager {
    // Used to load the 'trtcndkdemo' library on application startup.
    static {
        System.loadLibrary("trtcndkdemo");
    }
    public static native void initNativeTRTC();

    /**
     * 获取sdk版本
     * @return sdk版本
     */
    public static native String getSDKVersion();

    /**
     * 开启本地预览
     * @param frontCamera 是否是前置摄像头
     * @param view  承载的view
     */
    public static native void nativeStartLocalVideo(boolean frontCamera,TXCloudVideoView view);

    /**
     * 开启音频上行
     */
    public static native void startLocalAudio();
    /**
     * 进房
     */
    public static native void enterRoom(String roomID,String userID,String userSig,int sdkAppID);

    public static native  void nativeStartRemoteView(String userId, int streamType, TXCloudVideoView view);

    public static native void nativeDestroy();



}
