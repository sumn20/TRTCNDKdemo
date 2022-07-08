package com.project.trtcndkdemo;


import android.os.Bundle;

import com.project.trtcndkdemo.databinding.ActivitySimpleTrtcndkactivityBinding;
import com.project.trtcndkdemo.naviteUtils.JniCallBack;
import com.project.trtcndkdemo.naviteUtils.TRTCNativeManager;
import com.tencent.trtc.TRTCCloudDef;

public class SimpleTRTCNDKActivity extends BaseActivity {
    ActivitySimpleTrtcndkactivityBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding=ActivitySimpleTrtcndkactivityBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        bindToolbarWithBack(binding.toolbar);
        String userID=getIntent().getStringExtra("userID");
        String roomID=getIntent().getStringExtra("roomID");
        binding.toolbar.setTitle("房间号:"+roomID);
        TRTCNativeManager.nativeStartLocalVideo(true,binding.localVideo);
        TRTCNativeManager.startLocalAudio();
        TRTCNativeManager.enterRoom(roomID,userID);
        JniCallBack.setCallBak((userID1, available) -> {
            TRTCNativeManager.nativeStartRemoteView(userID1, TRTCCloudDef.TRTC_VIDEO_STREAM_TYPE_BIG,binding.remoteVideo);
        });
    }

    @Override
    protected void onDestroy() {
        TRTCNativeManager.nativeDestroy();
        super.onDestroy();

    }
}