# set minimum cmake version
cmake_minimum_required(VERSION 4.2 FATAL_ERROR)

# require C++11
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# project name and language
project(haru-opencv-web LANGUAGES CXX)

# 1. Find the OpenCV package
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV_INCLUDE_DIRS=${OpenCV_INCLUDE_DIRS}")
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
        modules/haru_httpserver.cpp)

# 3. Link OpenCV libraries to your executable
target_link_libraries(opencv-web ${OpenCV_LIBS})
target_include_directories(opencv-web PRIVATE ${OpenCV_INCLUDE_DIRS})