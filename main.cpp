#include "include/httplib.hpp"
#include <string>
#include <filesystem>
#include <thread>
#include "modules/opencv_utils.h"
#include "modules/file_utils.h"
#include "modules/photo_handler.h"
#include "modules/haru_ffmpeg.h"
#include "modules/file_utils.h"

using namespace haru;
// void create_video() {
//     std::string source = "/Users/developer/T9/travels/processed";
//     std::string export_path = "/Users/developer/T9/workshop/export-photoes-mp4";
//     std::string export_path_mp3_mp4 = "/Users/developer/T9/workshop/final-photoes-mp4";
//     std::string media_mp3_path = "/Users/developer/T9/workshop/media-mp3";
//     std::string media_mp3_processed_path = "/Users/developer/T9/workshop/media-mp3-export";
//     std::cout << "create_video::" << source << " to " << export_path << std::endl;
//     std::vector<std::string> export_mp4_files = make_video_from_photoes(source,export_path);
//     std::vector<std::string> mp3_files = getFiles(media_mp3_path,".mp3");
//     // std::string merged_mp3_output = "/Users/developer/T9/travels/play-music-export";
//     HaruMp3Files mp3_files_obj{.mp3_path = media_mp3_processed_path,.files = mp3_files};
//     for (std::string video_file : export_mp4_files) {
//         std::cout << "video => " << video_file << std::endl;
//         std::filesystem::path filePath(video_file);
//         std::string filename = export_path_mp3_mp4 + "/" + filePath.filename().string();
//         std::cout << "video with mp3 => " << filename << std::endl;
//         std::string mp3_filename = mp3_files_obj.merge_mp3();
//         std::cout << "merged mp3 => " << mp3_filename << std::endl;
//         add_mp3_to_mp4(mp3_filename,video_file,filename);
//     }
// }
void merge_mp3() {
    std::vector<std::string> export_mp4_files = {"one","two","three","four","five","six","seven","eight"};
    std::string merged_mp3_output = "/Users/developer/T9/travels/play-music-export";
    std::vector<std::string> mp3_files = getFiles("/Users/developer/T9/travels/play-music",".mp3");
    HaruMp3Files mp3_files_obj{.mp3_path = merged_mp3_output,.files = mp3_files};
    for (std::string video_file : export_mp4_files) {
        std::cout << "video => " << video_file << std::endl;
        std::string mp3_filename = mp3_files_obj.merge_mp3();
    }
}
void handle_photoes() {
    std::string source = "/Users/developer/T9/travels/sumsong";
    std::string destination = "/Users/developer/T9/travels/processed";
    process_filesystem(source, destination);
}
void test() {
    std::filesystem::path filePath("/Users/developer/T9/travels/export-workspace/20251202_080503.jpg");
    std::cout << filePath.extension() << std::endl;
    std::cout << filePath.stem() << std::endl;

}

int main() {
    // webMain();
    //create_video();
    // std::string mp1 = "/Users/developer/T9/travels/export-workspace/audio1.mp3";
    // std::string mp2 = "/Users/developer/T9/travels/export-workspace/audio2.mp3";
    // std::string output = "/Users/developer/T9/travels/export-workspace/audio-export.mp3";
    // concatenateMP3(mp1,mp2,output);
    // std::string mp3 = "/Users/developer/T9/travels/export-workspace/audio-export.mp3";
    // std::string mp4 = "/Users/developer/T9/travels/export-workspace/video.mp4";
    // std::string output = "/Users/developer/T9/travels/export-workspace/video-export.mp4";
    // merge_mp4_and_mp3(mp3,mp4,output);
    create_video();
    // merge_mp3();
    // handle_photoes();
    // test();
}