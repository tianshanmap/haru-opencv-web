//
// Created by developer on 2026-05-22.
//
#include <iostream>
#include "file_utils.h"
#include "opencv_utils.h"
#include "haru_random.h"

namespace haru {
    const double HARU_SCALE = 0.3;
    const int HARU_FRAME_WIDTH = 1240;
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
    void contract_frame(cv::VideoWriter &output,cv::Mat &frame,int repeat,double alpha,double beta) {
        cv::Mat *frame_target = contrast(frame,alpha,beta);
        for (int i = 0; i < repeat; i++) {
            output << *frame_target;
        }
        delete frame_target;
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
                    repeat_frame(output,*resized_img,1);
                    for (double i = 190; i > 0; i=i-10.0) {
                        output_shift_frame_vertically(output,*resized_img,i);
                    }
                    repeat_frame(output,*resized_img,5);
                    break;
                case 5:
                    repeat_frame(output,*resized_img,20);
                    break;
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
}