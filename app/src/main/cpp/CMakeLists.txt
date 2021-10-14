# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("trtcndkdemo")
set(jnilibs "${CMAKE_SOURCE_DIR}/../jniLibs")
# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
include_directories(
        include
        util
        sdkinterface
)
file(GLOB src-files
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/util/*.cpp
        ${CMAKE_SOURCE_DIR}/sdkinterface/*.cpp
        )
add_library( # Sets the name of the library.
        trtcndkdemo

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${src-files})


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)
add_library(liteavsdk SHARED IMPORTED )
set_target_properties(liteavsdk PROPERTIES IMPORTED_LOCATION ${jnilibs}/${ANDROID_ABI}/libliteavsdk.so)

add_library(soundtouch SHARED IMPORTED )
set_target_properties(soundtouch PROPERTIES IMPORTED_LOCATION ${jnilibs}/${ANDROID_ABI}/libsoundtouch.so)

add_library(traeimp-rtmp SHARED IMPORTED )
set_target_properties(traeimp-rtmp PROPERTIES IMPORTED_LOCATION ${jnilibs}/${ANDROID_ABI}/libtraeimp-rtmp.so)

add_library(txffmpeg SHARED IMPORTED )
set_target_properties(txffmpeg PROPERTIES IMPORTED_LOCATION ${jnilibs}/${ANDROID_ABI}/libtxffmpeg.so)

set(third-party-libs
        liteavsdk
        soundtouch
        traeimp-rtmp
        txffmpeg
        )
# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        trtcndkdemo

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        ${third-party-libs}
        EGL
        GLESv3
        android)