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
}