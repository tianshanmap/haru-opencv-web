#include <iostream>
#include "./opencv_utils.h"
#include "photo_handler.h"
#include "haru_ffmpeg.h"
#include "../include/json.hpp"

using json = nlohmann::json;
namespace harusvc {
    std::string create_video(std::string &image_path,std::string audio_path,std::string &video_path) {
        std::cout << "create_video :: image_path=" << image_path << std::endl;
        std::cout << "create_video :: audio_path=" << audio_path << std::endl;
        std::cout << "create_video :: video_path=" << video_path << std::endl;
        std::cout << "create_video :: process_photoes-started" << std::endl;
        haru::process_photoes(image_path,video_path);
        std::cout << "create_video :: add_mp3_to_mp4-started" << std::endl;
        haru::add_mp3_to_mp4(audio_path,video_path);
        std::cout << "create_video :: create result" << std::endl;
        json result;
        result["file"] = video_path;
        result["status"] = "success";
        std::cout << "create_video :: result-created" << std::endl;
        return result.dump();
    }
}
