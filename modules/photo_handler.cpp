//
// Created by developer on 2026-05-22.
//
#include <iostream>
#include <thread>
#include <filesystem>
#include "file_utils.h"
#include "opencv_utils.h"
#include "haru_random.h"

namespace haru {
    const double HARU_SCALE = 0.4;
    const int HARU_FRAME_WIDTH = 1512;
    const int HARU_FRAME_HEIGHT = 1024;
    const cv::Size HARU_IMAGE_SIZE = cv::Size(HARU_FRAME_WIDTH,HARU_FRAME_HEIGHT);
    const int HARU_CODEC = CV_FOURCC('a', 'v', 'c', '1');
    const int HARU_FPS = 5;

    void flip_frame_horizentally(cv::VideoWriter &output,cv::Mat &frame,int repeat) {
        cv::Mat flippedFrame;
        // ... assume frame is populated ...
        for (int i = 0; i < repeat; i++) {
            cv::flip(frame, flippedFrame, 1); // 1 means flipping horizontally
            output << flippedFrame;
        }
    }
    void flip_frame_vertically(cv::VideoWriter &output,cv::Mat &frame,int repeat) {
        cv::Mat flippedFrame;
        // ... assume frame is populated ...
        for (int i = 0; i < repeat; i++) {
            cv::flip(frame, flippedFrame, 0); // 1 means flipping horizontally
            output << flippedFrame;
        }
    }
    void grey_frame(cv::VideoWriter &output,cv::Mat &frame,int repeat) {
        cv::Mat *frame_target = grey(frame);
        for (int i = 0; i < repeat; i++) {
            output << *frame_target;
        }
        delete frame_target;
    }
    void contrast_frame(cv::VideoWriter &output,cv::Mat &frame,int repeat) {
        double beta = 0 - (repeat-1);
        for (int i = 0; i < repeat; i++) {
            cv::Mat *frame_target = contrast(frame,1.0,beta);
            output << *frame_target;
            delete frame_target;
            beta = beta + i;
        }
    }
    void blur_frame(cv::VideoWriter &output,cv::Mat &frame,int repeat) {
        cv::Mat mat;
        int initial_value = 5;
        for (int i = repeat; i > 0; i--) {
            cv::blur(frame, mat, cv::Size(i+5, i+5));
            output << mat;
        }
    }
    void repeat_frame(cv::VideoWriter &output,cv::Mat &frame,int repeat) {
        for (int i = 0; i < repeat; i++) {
            output << frame;
        }
    }
    void output_shift_frame_vertically(cv::VideoWriter &output,cv::Mat &frame,double shift) {
        cv::Mat *shiftedImage = shift_frame_vertically(frame,shift);
        output << *shiftedImage;
        delete shiftedImage;
    }
    void output_shift_frame_horizentally(cv::VideoWriter &output,cv::Mat &frame,double shift) {
        cv::Mat *shiftedImage = shift_frame_horizentally(frame,shift);
        output << *shiftedImage;
        delete shiftedImage;
    }
    /*
    ffmpeg -i video.mp4 -i audio1.mp3 -i audio2.mp3 -filter_complex \
    "[1:a][2:a]concat=n=2:v=0:a=1[seq]; \
    [seq]aloop=loop=-1:size=2e+09[looped]; \
    [looped]amix=inputs=1:duration=shortest[a]" \
    -shortest \
    -map 0:v -map "[a]" -c:v copy -shortest output.mp4
     */
    void rotate_frame(cv::VideoWriter &output,cv::Mat &frame,double angle,int repeat) {
        // cv::Mat dst;
        // cv::bitwise_not(frame, dst);
        // cv::Mat *frame1 = styleImage(frame);
        cv::Mat *frame_target = rotation(frame,angle);
        // cv::Mat *frame_target1 = contrast(*frame_target,2,1.0);
        for (int i = 0; i < repeat; i++) {
            output << *frame_target;
        }
        // delete frame1;
        delete frame_target;
    }
    void process_photoes(std::string path,std::string videoFile){
        HaruRandom haru_random(1,9);
        std::vector<std::string> files = getFiles(path,".jpeg");
        std::cout << "Total jpeg files to be handled => " << files.size() << std::endl;
        cv::VideoWriter output(videoFile, HARU_CODEC, HARU_FPS, HARU_IMAGE_SIZE);
        for (std::string file : files) {
            cv::Mat frame = cv::imread(file);
            // std::cout << "Handle file=> " << file << ",size=" << frame.size << std::endl;
            // cv::Mat resized_img;
            // Resize to 300x200 (Width x Height)
            // cv::resize(frame, resized_img, HARU_IMAGE_SIZE);
            cv::Mat *resized_img = resize_image(frame,HARU_SCALE,HARU_FRAME_WIDTH,HARU_FRAME_HEIGHT);
            // for (int i = 20; i >= 0; i=i-10) {
            //     rotate_frame(output,resized_img,i,1);
            // }
            // flip_frame_horizentally(output,resized_img,2);
            // for (int i = -20; i < 0; i=i+10) {
            //     rotate_frame(output,resized_img,i,1);
            // }
            int my_rd = haru_random.getRandom();
            // std::cout << "Random Number => " << my_rd << std::endl;
            switch (my_rd) {
                case 1:
                    repeat_frame(output,*resized_img,1);
                    for (double i = 0; i <= 400.0; i=i+20.0) {
                        output_shift_frame_horizentally(output,*resized_img,i);
                    }
                    repeat_frame(output,*resized_img,5);
                    break;
                case 2:
                    repeat_frame(output,*resized_img,1);
                    for (double i = 400; i > 0; i=i-20.0) {
                        output_shift_frame_horizentally(output,*resized_img,i);
                    }
                    repeat_frame(output,*resized_img,5);
                    break;
                case 3:
                    repeat_frame(output,*resized_img,1);
                    for (double i = 0; i <= 190.0; i=i+10.0) {
                        output_shift_frame_vertically(output,*resized_img,i);
                        // skin_smooth(frame,resized_img);
                        // output << resized_img;
                    }
                    repeat_frame(output,*resized_img,5);
                    break;
                case 4:
                    contrast_frame(output,*resized_img,20);
                    repeat_frame(output,*resized_img,5);
                    break;
                case 5:
                    contrast_frame(output,*resized_img,20);
                    repeat_frame(output,*resized_img,5);
                    break;
                    // case 5:
                //     repeat_frame(output,*resized_img,20);
                //     break;
                case 6:
                    for (int i = 90; i >= 0; i=i-10) {
                        rotate_frame(output,*resized_img,i,1);
                    }
                    repeat_frame(output,*resized_img,20);
                    break;
                case 7:
                    for (int i = -90; i < 0; i=i+10) {
                        rotate_frame(output,*resized_img,i,1);
                    }
                    repeat_frame(output,*resized_img,20);
                    break;
                case 8:
                    blur_frame(output,*resized_img,10);
                    repeat_frame(output,*resized_img,20);
                    break;
                case 9:
                    blur_frame(output,*resized_img,10);
                    repeat_frame(output,*resized_img,20);
                    break;
            }
            delete resized_img;
        }
        output.release();
        cv::destroyAllWindows();
        std::cout << "Write video to  => " << videoFile << std::endl;
    }

    std::vector<std::string> make_video_from_photoes(std::string source,std::string export_path) {
        std::vector<std::string> export_mp4_files;
        // std::string source = "/Users/developer/T9/travels/processed";
        // std::string export_path = "/Users/developer/T9/travels/export";
        std::vector<std::string> files;
        find_image_directory(source,files);
        std::vector<std::thread> thread_pool;
        for (auto file : files) {
            std::cout << "Process directory => " << file << std::endl;
            // std::string export_path = create_folder_under(file,"export");
            // std::cout << "Process export directory => " << export_path << std::endl;
            std::filesystem::path filepath(file);
            std::cout << "Process filepath => " << filepath.filename() << std::endl;
            // process_photoes(file,export_path + "/" + filepath.parent_path().filename().string() + ".mp4");
            std::string export_mp4_file = export_path + "/" + filepath.parent_path().filename().string() + ".mp4";
            export_mp4_files.push_back(export_mp4_file);
            std::thread th(process_photoes,file,export_mp4_file);
            thread_pool.push_back(std::move(th));
        }
        for (auto &th : thread_pool) {
            th.join();
        }
        return export_mp4_files;
    }
}