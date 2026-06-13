//
// Created by developer on 2026-06-08.
//
#include "web_models.h"
#include "../include/json.hpp"

#ifndef HARU_OPENCV_WEB_HARU_HTTP_HANDLERS_H
#define HARU_OPENCV_WEB_HARU_HTTP_HANDLERS_H
namespace haru {
    VideoCreateRequest get_video_create_request(const httplib::Request &req);
    VideoCreateRequestV1 get_video_create_request_v1(const httplib::Request &req);
    AudioCreateRequest get_audio_create_request(const httplib::Request &req);
    std::string get_audio_create_response(AudioCreateResponse &response);
};

#endif //HARU_OPENCV_WEB_HARU_HTTP_HANDLERS_H
