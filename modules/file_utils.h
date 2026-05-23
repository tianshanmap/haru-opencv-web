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
    void find_image_directory(std::string path,std::vector<std::string> &files);
    std::string create_folder_under(std::string pathname,std::string name);
}
#endif //HARU_OPENCV_WEB_FILE_UTILS_H
