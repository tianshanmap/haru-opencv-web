//
// Created by developer on 2026-06-08.
//
#include <vector>
#ifndef HARU_OPENCV_WEB_WEB_MODELS_H
#define HARU_OPENCV_WEB_WEB_MODELS_H
#include <string>
namespace haru {
    struct AudioCreateRequest {
        std::vector<std::string> audio_files;
    };
    struct AudioCreateResponse {
        std::string name;
    };
    struct VideoCreateRequest {
        std::string video_name;
        std::string image_path;
        std::vector<std::string> audio_files;
    };
    struct VideoCreateRequestV1 : public VideoCreateRequest {
        std::string audio_name;
        std::vector<std::string> image_files;
    };
    struct VideoCreateResponse {
        std::string name;
    };
}
#endif //HARU_OPENCV_WEB_WEB_MODELS_H
