#include "include/httplib.hpp"
#include <string>

#include "modules/opencv_utils.h"
#include "modules/file_utils.h"
#include "modules/photo_handler.h"

using namespace haru;
int main()
{
    // webMain();
    // std::string source = "/Users/developer/T9/travels/2026-01-14_2026-03-25";
    // std::string destination = "/Users/developer/T9/travels/processed";
    // process_filesystem(source, destination);
    // std::string destination = "/Users/developer/T9/travels/processed/2026-01-16-2026-01-23-singapore-maleka/jpeg";
    std::string source = "/Users/developer/T9/travels/processed";
    std::vector<std::string> files;
    find_image_directory(source,files);
    for (auto file : files) {
        std::cout << "Process directory => " << file << std::endl;
        std::string export_path = create_folder_under(file,"export");
        std::cout << "Process export directory => " << export_path << std::endl;
        process_photoes(file,export_path + "/export-photoes.mp4");
    }
    // std::string output = "/Users/developer/T9/travels/processed/2026-01-16-2026-01-23-singapore-maleka/export/malaka.mp4";
    // process_photoes(destination,output);
}//
// Created by developer on 2026-05-19.
//
