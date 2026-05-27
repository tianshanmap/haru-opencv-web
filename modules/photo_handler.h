//
// Created by developer on 2026-05-22.
//

#ifndef HARU_OPENCV_WEB_PHOTO_HANDLER_H
#define HARU_OPENCV_WEB_PHOTO_HANDLER_H
namespace haru {
    // void process_photoes(std::string path,std::string videoFile);
    void create_video();
    std::vector<std::string> make_video_from_photoes(std::string source,std::string export_path);
}
#endif //HARU_OPENCV_WEB_PHOTO_HANDLER_H
