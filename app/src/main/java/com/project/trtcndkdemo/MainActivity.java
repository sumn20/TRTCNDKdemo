package com.project.trtcndkdemo;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.widget.Toast;

import com.project.trtcndkdemo.databinding.ActivityMainBinding;
import com.project.trtcndkdemo.naviteUtils.TRTCNativeManager;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    protected static final int REQ_PERMISSION_CODE = 0x1000;
    // 权限个数计数，获取Android系统权限
    protected int mGrantedCount = 0;

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        binding.sdkVersion.setText(TRTCNativeManager.getSDKVersion());
        binding.nativeSimple.setOnClickListener(view -> {
            startActivity(new Intent(MainActivity.this,SimpleEnterActivity.class));

        });
        checkPermission();



    }
    //////////////////////////////////    动态权限申请   ////////////////////////////////////////

    protected boolean checkPermission() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            List<String> permissions = new ArrayList<>();
            if (PackageManager.PERMISSION_GRANTED != ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
                permissions.add(Manifest.permission.WRITE_EXTERNAL_STORAGE);
            }
            if (PackageManager.PERMISSION_GRANTED != ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA)) {
                permissions.add(Manifest.permission.CAMERA);
            }
            if (PackageManager.PERMISSION_GRANTED != ActivityCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO)) {
                permissions.add(Manifest.permission.RECORD_AUDIO);
            }
            if (PackageManager.PERMISSION_GRANTED != ActivityCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE)) {
                permissions.add(Manifest.permission.READ_EXTERNAL_STORAGE);
            }
            if (permissions.size() != 0) {
                ActivityCompat.requestPermissions(this,
                        permissions.toArray(new String[0]),
                        REQ_PERMISSION_CODE);
                return false;
            }
        }
        return true;
    }
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        switch (requestCode) {
            case REQ_PERMISSION_CODE:
                for (int ret : grantResults) {
                    if (PackageManager.PERMISSION_GRANTED == ret) {
                        mGrantedCount++;
                    }
                }
                if (mGrantedCount == permissions.length) {

                } else {
                    Toast.makeText(this, "用户没有允许需要的权限，加入通话失败", Toast.LENGTH_SHORT).show();
                }
                mGrantedCount = 0;
                break;
            default:
                break;
        }
    }
}