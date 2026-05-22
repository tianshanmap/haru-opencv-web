//
// Created by developer on 2026-05-19.
//
#include <iostream>
#include <vector>

#ifndef HARU_OPENCV_WEB_FILE_UTILS_H
#define HARU_OPENCV_WEB_FILE_UTILS_H
namespace haru {
    int process_filesystem(std::string path,std::string destination);
    std::vector<std::string> getFiles(std::string path,std::string extension);

}
#endif //HARU_OPENCV_WEB_FILE_UTILS_H
