#include "include/httplib.hpp"
#include <string>
#include <filesystem>
#include <thread>
#include "modules/opencv_utils.h"
#include "modules/file_utils.h"
#include "modules/photo_handler.h"

using namespace haru;
void worker() {
    std::cout << "Thread is working...\n";
}
int main()
{
    std::thread t(worker);
     // webMain();
    // std::string source = "/Users/developer/T9/travels/2026-01-14_2026-03-25";
    // std::string destination = "/Users/developer/T9/travels/processed";
    // process_filesystem(source, destination);
    // std::string destination = "/Users/developer/T9/travels/processed/2026-01-16-2026-01-23-singapore-maleka/jpeg";
    std::string source = "/Users/developer/T9/travels/processed";
    std::string export_path = "/Users/developer/T9/travels/export";
    std::vector<std::string> files;
    find_image_directory(source,files);
    std::vector<std::thread> thread_pool;
    for (auto file : files) {
        std::cout << "Process directory => " << file << std::endl;
        // std::string export_path = create_folder_under(file,"export");
        // std::cout << "Process export directory => " << export_path << std::endl;
        std::filesystem::path filepath(file);
        std::cout << "Process filepath => " << filepath.filename() << std::endl;
        // process_photoes(file,export_path + "/" + filepath.parent_path().filename().string() + ".mp4");
        std::thread th(process_photoes,file,export_path + "/" + filepath.parent_path().filename().string() + ".mp4");
        thread_pool.push_back(std::move(th));
    }
    for (auto &th : thread_pool) {
        th.join();
    }
    // std::string output = "/Users/developer/T9/travels/processed/2026-01-16-2026-01-23-singapore-maleka/export/malaka.mp4";
    // process_photoes(destination,output);
    // std::string path = "/Users/developer/T9/travels/processed/2026-01-16-2026-01-23-singapore-maleka/jpeg/IMG_2257.jpeg";
    // play_image_with_background(path,2048,2048);
}//
// Created by developer on 2026-05-19.
//
