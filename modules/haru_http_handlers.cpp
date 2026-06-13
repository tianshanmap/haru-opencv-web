#include "web_models.h"
#include "../include/json.hpp"
#include "../include/httplib.hpp"

using json = nlohmann::json;
namespace haru {
    VideoCreateRequest get_video_create_request(const httplib::Request &req) {
        json incoming_json = json::parse(req.body);
        VideoCreateRequest request;
        request.image_path = incoming_json["image_path"];
        request.video_name = incoming_json["video_name"];
        request.audio_files = incoming_json["audio_files"];
        return request;
    }
    VideoCreateRequestV1 get_video_create_request_v1(const httplib::Request &req) {
        json incoming_json = json::parse(req.body);
        VideoCreateRequestV1 request;
        request.image_path = incoming_json["image_path"];
        request.audio_name = incoming_json["audio_name"];
        request.video_name = incoming_json["video_name"];
        request.image_files = incoming_json["image_files"];
        return request;
    }
    AudioCreateRequest get_audio_create_request(const httplib::Request &req) {
        json incoming_json = json::parse(req.body);
        AudioCreateRequest request;
        request.audio_files = incoming_json["audio_files"];
        return request;
    }
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AudioCreateResponse, name);
    std::string get_audio_create_response(AudioCreateResponse &response) {
        nlohmann::json j = response;
        return j.dump();
    }

}