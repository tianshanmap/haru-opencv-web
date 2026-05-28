#include <string>
#include <filesystem>
#include "include/httplib.hpp"
#include "modules/haru_yaml.h"
#include "modules/opencv_utils.h"
#include "modules/file_utils.h"
#include "modules/photo_handler.h"
#include "modules/haru_ffmpeg.h"
#include "modules/haru_httpserver.h"
#include <simplelogger/simple_logger.hpp>
using namespace haru;
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
    YamlConfig config{.yaml_path="../config/application.yaml"};
    config.load_yaml();
    SimpleLogger &logger = SimpleLogger::getInstance();
    logger.configure("../log/log.txt",LogLevel::INFO);
    logger.debug("debug");
    logger.info("info");
    logger.warning("warning");
    logger.error("error");
    webMain(config);
    // load_video("/Users/developer/T9/document/seijin/Maki Kozue is a perfect sex slave in every way [kimvvpkb353].mp4","/Users/developer/T9/document/seijin/image");
    // std::string filename1 = "/Users/developer/T9/document/seijin/image/frame_206.jpg";
    // std::string filename2 = "/Users/developer/T9/travels/processed/s25-malasia/jpeg/20260119_125700.jpeg";
    // combine_image(filename1,filename2);
    // combine_overlay(filename1,filename2);
    //create_video();
    // std::string mp1 = "/Users/developer/T9/travels/export-workspace/audio1.mp3";
    // std::string mp2 = "/Users/developer/T9/travels/export-workspace/audio2.mp3";
    // std::string output = "/Users/developer/T9/travels/export-workspace/audio-export.mp3";
    // concatenateMP3(mp1,mp2,output);
    // std::string mp3 = "/Users/developer/T9/travels/export-workspace/audio-export.mp3";
    // std::string mp4 = "/Users/developer/T9/travels/export-workspace/video.mp4";
    // std::string output = "/Users/developer/T9/travels/export-workspace/video-export.mp4";
    // merge_mp4_and_mp3(mp3,mp4,output);
    // YamlConfig config{.yaml_path="../config/application.yaml"};
    // config.load_yaml();
    // std::cout << config.source << std::endl;
    // std::cout << config.export_path << std::endl;
    // create_video(config);
    // merge_mp3();
    // handle_photoes();
    // test();
}