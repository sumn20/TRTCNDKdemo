package com.project.trtcndkdemo.naviteUtils;

public class JniCallBack {
    private static callBack CALLBACK;



    public static void setCallBak(callBack callBack) {
        CALLBACK = callBack;
    }

    /**
     * jni 调用java方法
     */
    public static void  jniCallUserVideoAvailable(String userID, boolean available) {
        CALLBACK.onUserVideoAvailable(userID, available);
    }


    public interface callBack {
        void onUserVideoAvailable(String userID, boolean available);
    }
}
