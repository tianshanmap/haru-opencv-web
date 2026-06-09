//
// Created by developer on 2026-06-08.
//
#include "web_models.h"

#ifndef HARU_OPENCV_WEB_HARU_HTTP_HANDLERS_H
#define HARU_OPENCV_WEB_HARU_HTTP_HANDLERS_H
namespace haru {
    VideoCreateRequest get_video_create_request(const httplib::Request &req);
};

#endif //HARU_OPENCV_WEB_HARU_HTTP_HANDLERS_H
