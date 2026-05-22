#include <filesystem>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

int g_slider_position = 0;
int g_run = 1, g_dontset = 0; //start out in single step mode
cv::VideoCapture g_cap;

void test() {
    // Initializing string`
    std::string str = "geeksforgeeks";

    // Declaring iterator
    std::string::iterator it;

    // Declaring reverse iterator
    std::string::reverse_iterator it1;
    std::cout<<"Str:"<<str<<"\n";
    // Displaying string
    std::cout << "The string using forward iterators is : ";
    for (it = str.begin(); it != str.end(); it++){
        if(it == str.begin()) *it='G';
        std::cout << *it;
    }
}
int load_image() {
    // Read the image file
    cv::Mat image = cv::imread("/Users/developer/Documents/book/2026-01-27-kaula-lumpur-national-mosque/IMG_2963.jpeg", cv::IMREAD_COLOR);

    // Check for failure
    if (image.empty()) {
        std::cout << "Could not read the image" << std::endl;
        return -1;
    }

    std::string window_name = "My OpenCV Window";
    window_name.pop_back();
    const char* c_string = window_name.c_str();

    // Create a window
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    // Show the image
    cv::imshow(window_name, image);
    // Wait for a keystroke in the window
    cv::waitKey(0);
}

void onTrackbarSlide( int pos, void *) {
    g_cap.set( cv::CAP_PROP_POS_FRAMES, pos );
    if( !g_dontset )
        g_run = 1;
    g_dontset = 0;
}
void save_image(cv::Mat& frame,std::string filename) {
    cv::imwrite(filename, frame);
}
void load_video(std::string filename,std::filesystem::path parent_path) {
    cv::namedWindow( "Example2_4", cv::WINDOW_AUTOSIZE );
    g_cap.open(filename);
    int frames = (int) g_cap.get(cv::CAP_PROP_FRAME_COUNT);
    int tmpw = (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int tmph = (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    std::cout << "Video has " << frames << " frames of dimensions("
    << tmpw << ", " << tmph << ")." << std::endl;
    cv::createTrackbar("Position", "Example2_4", &g_slider_position, frames,
    onTrackbarSlide);
    cv::Mat frame;
    for(;;) {
        if( g_run != 0 ) {
            g_cap >> frame; if(frame.empty()) break;
            int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
            g_dontset = 1;
            cv::setTrackbarPos("Position", "Example2_4", current_pos);
            cv::imshow( "Example2_4", frame );
            g_run-=1;
        }
        char c = (char) cv::waitKey(10);
        //single mode
        if( c == 's' ){
            g_run = 1;
            std::cout << "Single step, run = " << g_run << std::endl;
        }
        //run mode
        if( c == 'r' ) {
            g_run = -1;
            std::cout << "Run mode, run = " << g_run << std::endl;
        }
        //save the image to the file system
        if( c == 'w' ) {
            std::string filename = parent_path.string() + "/frame_" + std::to_string(g_slider_position) + ".jpg";
            save_image(frame,filename);
            std::cout << "Save mode, run = " << g_run << std::endl;
            cv::namedWindow( "Example2_5-in", cv::WINDOW_AUTOSIZE );
            cv::namedWindow( "Example2_5-out", cv::WINDOW_AUTOSIZE );
            cv::Mat out;
            cv::GaussianBlur( frame, out, cv::Size(5,5), 3, 3);
            cv::GaussianBlur( out, out, cv::Size(5,5), 3, 3);
            cv::imshow( "Example2_5-in", frame );
            cv::imshow( "Example2_5-out", out );
        }
        if( c == 27 )
            break;
    }
}
void show_path(std::filesystem::path path) {
    std::cout << path << std::endl;
    std::cout << path.filename() << std::endl;
    std::cout << path.stem() << std::endl;
    std::cout << path.extension() << std::endl;
    std::cout << path.parent_path() << std::endl;
    std::cout << path.string() << std::endl;
    std::cout << path.has_filename() << std::endl;
    std::cout << path.has_parent_path() << std::endl;
}

std::vector<std::string> getFiles(std::string path) {
    std::vector<std::string> files;
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".jpeg") {
            files.push_back(entry.path().string());
        }
    }
    return files;
}

void create_movie(std::vector<std::string> files,std::string filename) {
    cv::Size frame_size(900, 900); // Set the expected size of your images
    const double fps = 0.5;
    cv::VideoWriter writer(filename, cv::VideoWriter::fourcc('M','J','P','G'), fps, frame_size);
    for(auto file:files) {
        cv::Mat frame = cv::imread(file);
        if (frame.size() != frame_size) {
            resize(frame, frame, frame_size);
        }
        writer.write(frame);
    }
}

cv::Mat& rotate_image(cv::Mat& frame,cv::Mat& rotated_image,double angle) {
    cv::Point2f center((frame.cols - 1) / 2.0, (frame.rows - 1) / 2.0);
    // using getRotationMatrix2D() to get the rotation matrix
    cv::Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0);
    warpAffine(frame, rotated_image, rotation_matix, frame.size());
    return rotated_image;
}

void load_image_from_url(std::vector<std::string> files) {
    std::string window_name = "my_window";
    std::string window_name_grey = "my_grey_window";
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    int current_pos = 0;
    for (;;) {
        std::string filename = files[current_pos];
        cv::Mat frame = cv::imread(filename);
        // cv::Mat grey_frame;
        // cv::cvtColor(frame, grey_frame, cv::COLOR_BGR2GRAY);
        cv::imshow(window_name, frame);
        // cv::imshow(window_name_grey, grey_frame);
        cv::Mat second_frame;
        //flipCode : 0 => horizontal, 1 => vertical
        // cv::flip(frame, second_frame, 0);
        // cv::normalize(frame, second_frame, 70, 230, cv::NORM_MINMAX);
        // rotate_image(frame,second_frame,30);
        cv::Mat mask;
        inRange(frame, cv::Scalar(255, 255, 255), cv::Scalar(255, 255, 255), mask);
        frame.setTo(cv::Scalar(0, 0, 0), mask);
        cv::imshow(window_name_grey, frame);
        // double alpha = 0.5;
        // double beta = 1.0 - alpha;
        // cv::addWeighted(grey_frame, alpqha, frame, beta, 0.0, frame);

        //handle input key stroke
        char c = (char) cv::waitKey(3000);
        std::cout << "c = " << c << std::endl;
        if (c == 'p' && current_pos > 0) {
            current_pos--;
        } else if (c == 'n' && current_pos < files.size() - 1) {
            current_pos++;
        } else if (c == 'q') {
            break;
        } else if (c == 's') {
            continue;
        } else {
            if (current_pos < files.size() - 1)
                current_pos++;
        }
    }
    // for(auto file:files) {
    //     // std::cout << file << std::endl;
    //     // Show the image
    //     cv::Mat frame = cv::imread(file);
    //     cv::imshow(window_name, frame);
    //     cv::waitKey(2000);
    // }
}
int main() {
    //test();
    // load_image();
    std::string filename = "/Users/developer/Documents/book/movie/2030_trailer.mp4";
    std::filesystem::path path(filename);
    show_path(path);
    // load_video(filename,path.parent_path());
    std::string directory = "/Users/developer/Documents/book/2026-01-31-genting-highlands-klcc-malaysia";
    std::vector<std::string> files = getFiles(directory);
    std::cout << "Show files in " << directory << std::endl;
    // create_movie(files,"/Users/developer/Documents/book/movie/kaula-lumpur.avi");
    load_image_from_url(files);
    return 0;
}
