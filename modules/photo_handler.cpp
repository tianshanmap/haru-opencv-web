//
// Created by developer on 2026-05-22.
//
#include <iostream>
#include "file_utils.h"
#include "opencv_utils.h"
#include "haru_random.h"

namespace haru {
    cv::Size S = cv::Size(800,600);
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
        cv::Mat *frame_target = rotation(frame,angle);
        // cv::Mat *frame_target1 = contrast(*frame_target,2,1.0);
        for (int i = 0; i < repeat; i++) {
            output << *frame_target;
        }
        delete frame_target;
    }
    void process_photoes(std::string path,std::string videoFile){
        std::vector<std::string> files = getFiles(path,".jpeg");
        std::cout << "files.size() => " << files.size() << std::endl;
        cv::VideoWriter output(videoFile, CV_FOURCC('H', '2', '6', '4'), 5, S);
        for (std::string file : files) {
            cv::Mat frame = cv::imread(file);
            // std::cout << "Handle file=> " << file << ",size=" << frame.size << std::endl;
            cv::Mat resized_img;
            // Resize to 300x200 (Width x Height)
            cv::resize(frame, resized_img, S);
            // for (int i = 20; i >= 0; i=i-10) {
            //     rotate_frame(output,resized_img,i,1);
            // }
            // flip_frame_horizentally(output,resized_img,2);
            // for (int i = -20; i < 0; i=i+10) {
            //     rotate_frame(output,resized_img,i,1);
            // }
            int my_rd = getRandom();
            // std::cout << "Random Number => " << my_rd << std::endl;
            switch (my_rd) {
                case 1:
                    repeat_frame(output,resized_img,1);
                    for (double i = 0; i <= 400.0; i=i+20.0) {
                        output_shift_frame_horizentally(output,resized_img,i);
                    }
                    break;
                case 2:
                    repeat_frame(output,resized_img,1);
                    for (double i = 400; i > 0; i=i-20.0) {
                        output_shift_frame_horizentally(output,resized_img,i);
                    }
                    break;
                case 3:
                    repeat_frame(output,resized_img,1);
                    for (double i = 0; i <= 190.0; i=i+10.0) {
                        output_shift_frame_vertically(output,resized_img,i);
                        // skin_smooth(frame,resized_img);
                        // output << resized_img;
                    }
                    break;
                case 4:
                    repeat_frame(output,resized_img,1);
                    for (double i = 190; i > 0; i=i-10.0) {
                        output_shift_frame_vertically(output,resized_img,i);
                    }
                    break;
                case 5:
                    repeat_frame(output,resized_img,20);
                    break;
                case 6:
                    for (int i = 90; i >= 0; i=i-10) {
                        rotate_frame(output,resized_img,i,1);
                    }
                    repeat_frame(output,resized_img,20);
                    break;
                case 7:
                    for (int i = -90; i < 0; i=i+10) {
                        rotate_frame(output,resized_img,i,1);
                    }
                    repeat_frame(output,resized_img,20);
                    break;
            }
        }
        output.release();
        cv::destroyAllWindows();
        std::cout << "Write video to  => " << videoFile << std::endl;
    }
}