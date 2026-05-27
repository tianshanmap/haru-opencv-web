extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}
#include <iostream>
#include <filesystem>
#include <vector>
#include <sstream>
#include <fstream>
#include <format>
#include "haru_random.h"
#include "haru_ffmpeg.h"
namespace haru {
    const int HARU_RANDOM_FFMPEG_MIN = 1;
    const int HARU_RANDOM_FFMPEG_MAX = 18;
    HaruRandom haru_random_ffmpeg(HARU_RANDOM_FFMPEG_MIN,HARU_RANDOM_FFMPEG_MAX);
    void add_mp3_to_mp4(std::string mp3,std::string mp4,std::string output) {
        HaruFFMpegMergeCMD cmd(mp3,mp4,output);
        std::cout << cmd.get_command() << std::endl;
        std::system(cmd.get_command().c_str());
    }
}
