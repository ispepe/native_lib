# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("nativeflutterlibs")

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")


add_library(gsgStitch
        SHARED
        IMPORTED
        )

set_target_properties(
        gsgStitch
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/libgsgStitch.so
)

#定义变量ocvlibs使后面的命令可以使用定位具体的库文件
#set(opencvlibs "${CMAKE_SOURCE_DIR}/libs")

#增加OpenCV 动态库
add_library(libopencv_java4 SHARED IMPORTED)

# 建立链接
set_target_properties(
        libopencv_java4
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/libopencv_java4.so
)

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib
        gsgStitch
        libopencv_java4
        )