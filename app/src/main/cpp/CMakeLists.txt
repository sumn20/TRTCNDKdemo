# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.10.2)
project("trtcndkdemo")
set(jnilibs "${CMAKE_SOURCE_DIR}/../jniLibs")
include_directories(
        include
        util
        sdkinterface
        third_party
        third_party/boringssl/openssl
)
file(GLOB src-files
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/util/*.cpp
        ${CMAKE_SOURCE_DIR}/sdkinterface/*.cpp
        )
add_library(
        trtcndkdemo
        SHARED
        ${src-files})
#log库
find_library(
        log-lib

        log)
#zlib库
find_library(
        libz-lib
        z)
#TRTC so库
add_library(liteavsdk SHARED IMPORTED )
set_target_properties(liteavsdk PROPERTIES IMPORTED_LOCATION ${jnilibs}/${ANDROID_ABI}/libliteavsdk.so)

add_library(txsoundtouch SHARED IMPORTED )
set_target_properties(txsoundtouch PROPERTIES IMPORTED_LOCATION ${jnilibs}/${ANDROID_ABI}/libtxsoundtouch.so)

add_library(txffmpeg SHARED IMPORTED )
set_target_properties(txffmpeg PROPERTIES IMPORTED_LOCATION ${jnilibs}/${ANDROID_ABI}/libtxffmpeg.so)

#boringssl相关
add_library(ssl STATIC IMPORTED )
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION ${jnilibs}/${ANDROID_ABI}/libssl.a)

add_library(crypto STATIC IMPORTED )
set_target_properties(crypto PROPERTIES IMPORTED_LOCATION ${jnilibs}/${ANDROID_ABI}/libcrypto.a)


set(third-party-libs
        liteavsdk
        txffmpeg
        txsoundtouch
        ssl
        crypto
        )

target_link_libraries(
        trtcndkdemo
        ${log-lib}
        ${libz-lib}
        ${third-party-libs}
        EGL
        GLESv3
        android
        )