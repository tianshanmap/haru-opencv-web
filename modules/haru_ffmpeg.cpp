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
    std::string get_filename(std::string &path,std::string ext) {
        std::filesystem::path filePath(path);
        return filePath.parent_path().filename().string() + ext;
    }
    void combine_video(std::vector<std::string> files,std::string export_path,std::string ext) {
        for (std::string file : files) {
            std::string file_output_mov = export_path + "/" + get_filename(file,ext);
            HaruFFMpegMergeVideoCMD cmd(file,file_output_mov);
            std::cout << "combine_video=>" << cmd.get_command() << std::endl;
            std::system(cmd.get_command().c_str());
            // std::string file_output_mp4 = export_path + "/" + get_filename(file,".mp4");
            // HaruFFMpegMovToMp4CMD cmd1(file_output_mov,file_output_mp4);
            // std::cout << "combine_video=>" << cmd1.get_command() << std::endl;
            // std::system(cmd1.get_command().c_str());
        }
    }
    void convert_mov_mp4(std::string mov,std::string mp4) {
        HaruFFMpegMovToMp4CMD cmd(mov,mp4);
        std::cout << "convert_mov_mp4=>" << cmd.get_command() << std::endl;
        std::system(cmd.get_command().c_str());
    }
}
