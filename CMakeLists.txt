# set minimum cmake version
cmake_minimum_required(VERSION 4.2 FATAL_ERROR)

# require C++11
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET 26.0)

# project name and language
project(haru-opencv-web LANGUAGES CXX)

# 1. Find the OpenCV package
find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)

# Search for the required FFmpeg components
pkg_check_modules(FFMPEG REQUIRED IMPORTED_TARGET
        libavcodec
        libavformat
        libavutil
        libswscale
)
message(STATUS "OpenCV_INCLUDE_DIRS=${OpenCV_INCLUDE_DIRS}")
message(STATUS "CMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET}")

include(FetchContent)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG master # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
FetchContent_MakeAvailable(yaml-cpp)

# main code
add_executable(opencv-web
        main.cpp
        modules/file_utils.cpp
        modules/file_utils.h
        modules/opencv_utils.cpp
        modules/opencv_utils.h
        modules/haru_random.h
        modules/photo_handler.cpp
        modules/photo_handler.h
        modules/haru_httpserver.cpp
        modules/haru_ffmpeg.cpp
        modules/haru_ffmpeg.h
        modules/haru_yaml.h
        modules/haru_httpserver.h
        modules/simple_logger.cpp
        modules/simple_logger.h
)

# 3. Link OpenCV libraries to your executable
target_link_libraries(opencv-web ${OpenCV_LIBS} PkgConfig::FFMPEG yaml-cpp::yaml-cpp)
target_include_directories(opencv-web PRIVATE ${OpenCV_INCLUDE_DIRS})
target_include_directories(opencv-web PRIVATE PkgConfig::FFMPEG)
