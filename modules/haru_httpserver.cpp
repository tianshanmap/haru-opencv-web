#include <iostream>

#include "haru_yaml.h"
#include "../include/httplib.hpp"
#include "opencv_utils.h"
namespace haru {
    int webMain(YamlConfig &config)
    {
        // std::cout is used to print text to the console
        std::cout << "Web application is listening at " << config.host << ":" << config.port << "..." << std::endl;
        httplib::Server svr;
        // http GET
        svr.Get("/hi", [](const httplib::Request &req, httplib::Response &res)
                {
            res.set_header("X-Custom-Header", "MyValue");
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content("Hello!", "text/plain"); });
        // With Query Parameter
        svr.Get("/search", [](const auto &req, auto &res)
                {
            auto q = req.get_param_value("q");
            res.set_content("Query: " + q, "text/plain"); });
        // With Path parameter : http://localhost:8080/users/234
        svr.Get("/users/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            res.set_content("User ID: " + id, "text/plain"); });
        // With Path parameter : http://localhost:8080/users/234/posts/45
        svr.Get("/users/:user_id/posts/:post_id", [](const auto &req, auto &res)
                {
            auto user_id = req.path_params.at("user_id");
            auto post_id = req.path_params.at("post_id");
            res.set_content("User: " + user_id + ", Post: " + post_id, "text/plain"); });
        // RegEX files/34 matches but files/abc not
        svr.Get(R"(/files/(\d+))", [](const auto &req, auto &res)
                {
            auto id = req.matches[1];  // First capture group
            res.set_content("File ID: " + std::string(id), "text/plain"); });
        // http header
        svr.Get("/check", [](const auto &req, auto &res)
                {
            auto auth = req.get_header_value("Authorization");
            res.set_content("Auth: " + auth, "text/plain"); });

        // http POST
        svr.Post("/post", [](const auto &req, auto &res)
                 {
            // Echo the body back to the client
            res.set_content(req.body, "text/plain"); });
        // Read the post parameter
        svr.Post("/submit", [](const auto &req, auto &res)
                 {
            std::string result;
            for (auto &[key, val] : req.params) {
                result += key + " = " + val + "\n";
            }
            res.set_content(result, "text/plain"); });

        // http file upload
        svr.Post("/upload", [](const auto &req, auto &res)
                 {
            auto f = req.form.get_file("file");
            auto content = f.filename + " (" + std::to_string(f.content.size()) + " bytes)";
            res.set_content(content, "text/plain"); });

        // Set status code
        svr.Get("/not-found", [](const auto &req, auto &res)
                {
            res.status = 404;
            res.set_content("Not found", "text/plain"); });

        // Set Response Header
        svr.Get("/with-header", [](const auto &req, auto &res)
                {
            res.set_header("X-Custom", "my-value");
            res.set_content("Hello!", "text/plain"); });

        // Set Response Header
        svr.Get("/image/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            cv::Mat *mat = readVideo(frame_id,filename,image_data);
            delete mat;
            std::string s(image_data.begin(), image_data.end());
            std::cout << "/image/" + id + "=> length="<< s.length() << std::endl;
            res.set_content(s, "image/jpeg"); });

        svr.Get("/image/transform/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            cv::Mat *mat = readVideo(frame_id,filename,image_data);
            cv::Mat *rotated_mat = rotation(*mat,30);
            convertImage(*rotated_mat,image_data);
            delete mat;
            delete rotated_mat;
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });

        svr.Get("/image/rotation/:id/:angle", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto angle_id = req.path_params.at("angle");
            auto frame_id = std::stoi(id);
            auto angle = std::stod(angle_id);
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            cv::Mat *mat = readVideo(frame_id,filename,image_data);
            cv::Mat *rotated_mat = rotation(*mat,angle);
            convertImage(*rotated_mat,image_data);
            delete mat;
            delete rotated_mat;
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });

        svr.Get("/image/grey/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            cv::Mat *mat = readVideo(frame_id,filename,image_data);
            cv::Mat *rotated_mat = grey(*mat);
            convertImage(*rotated_mat,image_data);
            delete mat;
            delete rotated_mat;
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });
        svr.Get("/image/blur/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            cv::Mat *mat = readVideo(frame_id,filename,image_data);
            cv::Mat *rotated_mat = blurImage(*mat);
            convertImage(*rotated_mat,image_data);
            delete mat;
            delete rotated_mat;
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });
        svr.Get("/image/gaussinblur/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            cv::Mat *mat = readVideo(frame_id,filename,image_data);
            cv::Mat *rotated_mat = gaussinblurImage(*mat);
            convertImage(*rotated_mat,image_data);
            delete mat;
            delete rotated_mat;
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });
        svr.Get("/image/medianblur/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            cv::Mat *mat = readVideo(frame_id,filename,image_data);
            cv::Mat *rotated_mat = medianblurImage(*mat);
            convertImage(*rotated_mat,image_data);
            delete mat;
            delete rotated_mat;
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });
        svr.Get("/image/flip_v/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            cv::Mat *mat = readVideo(frame_id,filename,image_data);
            cv::Mat *rotated_mat = flipImage(*mat,0);
            convertImage(*rotated_mat,image_data);
            delete mat;
            delete rotated_mat;
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });
        svr.Get("/image/flip_h/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            cv::Mat *mat = readVideo(frame_id,filename,image_data);
            cv::Mat *rotated_mat = flipImage(*mat,1);
            convertImage(*rotated_mat,image_data);
            delete mat;
            delete rotated_mat;
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });
        svr.Get("/image/normalize/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            cv::Mat *mat = readVideo(frame_id,filename,image_data);
            cv::Mat *rotated_mat = normalizeImage(*mat);
            convertImage(*rotated_mat,image_data);
            delete mat;
            delete rotated_mat;
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });
        svr.Get("/image/contrast/:id/:alpha/:beta", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto alpha = std::stod(req.path_params.at("alpha"));
            auto beta = std::stoi(req.path_params.at("beta"));
            auto frame_id = std::stoi(id);
            cv::Mat frame;
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            read_frame(frame_id,filename,frame);
            contrastImage(frame,image_data,alpha,beta);
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });
        svr.Get("/image/filter/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            cv::Mat frame;
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            read_frame(frame_id,filename,frame);
            float vertical_fk[3][3] = {
                {-1, -1, -1},
                {-1, 9, -1},
                {-1, -1, -1}};
            cv::Mat *filtered_image = image_filter(frame,vertical_fk);
            convertImage(*filtered_image,image_data);
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });

        svr.Options("/image/filter2D", [](const auto &req, auto &res)
                    { res.set_header("Access-Control-Allow-Origin", "*"); });
        svr.Post("/image/filter2D", [](const auto &req, auto &res)
                 {
                     std::cout << "/image/filter2D...dump headers..." << std::endl;
                     for (const auto &header : req.headers)
                     {
                         std::cout << header.first << ": " << header.second << std::endl;
                     }
                     res.set_header("Access-Control-Allow-Origin", "*");
                     std::cout << "/image/filter2D..." << std::endl;
                     std::string rows[3];
                     std::string frame_str = req.form.get_field("frame");
                     rows[0] = req.form.get_field("row1");
                     rows[1] = req.form.get_field("row2");
                     rows[2] = req.form.get_field("row3");
                     int frame_id = 0;
                     if (!frame_str.empty())
                     {
                         frame_id = std::stoi(frame_str);
                     }
                     int count = 0;
                     cv::Mat frame;
                     Matrix33 matrix = convertMatrix(rows, 3);
                     std::string filename = getVideo();
                         read_frame(frame_id, filename, frame);
                     cv::Mat *filtered_image = image_filter(frame, matrix.vertical_fk);
                     std::vector<uchar> image_data;
                     convertImage(*filtered_image, image_data);
                     delete filtered_image;

                     std::string s(image_data.begin(), image_data.end());
                     std::cout << "/image/filter2D...Completed" << s.length() << std::endl;
                     res.set_content(s, "image/jpeg");
                 });
        svr.Post("/image/filter2DV1", [](const auto &req, auto &res)
                 {
                     // std::cout << "/image/filter2D...dump headers..." << std::endl;
                     // for (const auto& header : req.headers) {
                     //     std::cout << header.first << ": " << header.second << std::endl;
                     // }
                     res.set_header("Access-Control-Allow-Origin", "*");
                     std::cout << "/image/filter2DV1--------------------..." << std::endl;
                     std::string frame_str = req.form.get_field("frame");
                     int frame_id = 0;
                     if (!frame_str.empty())
                     {
                         frame_id = std::stoi(frame_str);
                     }
                     int count = 0;
                     cv::Mat frame;
                     // Matrix33 matrix = convertMatrix(rows,3);
                     Matrix33 matrix;
                     std::cout << "/image/filter2DV1-----***---------------matrix.vertical_fk" << matrix.vertical_fk << std::endl;
                     for (int i = 0; i < 3; i++)
                     {
                         for (int j = 0; j < 3; j++)
                         {
                             std::cout << "(" << i << j << ")=" << matrix.vertical_fk[i][j] << " ";
                         };
                         std::cout << std::endl;
                     }

                     std::cout << "/image/filter2DV1-----r11---------------  " << req.form.get_field("r11") << std::endl;
                     std::cout << "/image/filter2DV1-----r12---------------  " << req.form.get_field("r12") << std::endl;
                     std::cout << "/image/filter2DV1-----r13---------------  " << req.form.get_field("r13") << std::endl;
                     std::cout << "/image/filter2DV1-----r21---------------  " << req.form.get_field("r21") << std::endl;
                     std::cout << "/image/filter2DV1-----r22---------------  " << req.form.get_field("r22") << std::endl;
                     std::cout << "/image/filter2DV1-----r23---------------  " << req.form.get_field("r23") << std::endl;
                     std::cout << "/image/filter2DV1-----r31---------------  " << req.form.get_field("r31") << std::endl;
                     std::cout << "/image/filter2DV1-----r32---------------  " << req.form.get_field("r32") << std::endl;
                     std::cout << "/image/filter2DV1-----r33---------------  " << req.form.get_field("r33") << std::endl;
                     matrix.vertical_fk[0][0] = std::stof(req.form.get_field("r11"));
                     matrix.vertical_fk[0][1] = std::stof(req.form.get_field("r12"));
                     matrix.vertical_fk[0][2] = std::stof(req.form.get_field("r13"));
                     matrix.vertical_fk[1][0] = std::stof(req.form.get_field("r21"));
                     matrix.vertical_fk[1][1] = std::stof(req.form.get_field("r22"));
                     matrix.vertical_fk[1][2] = std::stof(req.form.get_field("r23"));
                     matrix.vertical_fk[2][0] = std::stof(req.form.get_field("r31"));
                     matrix.vertical_fk[2][1] = std::stof(req.form.get_field("r32"));
                     matrix.vertical_fk[2][2] = std::stof(req.form.get_field("r33"));
                     std::cout << "------------------------------" << std::endl;
                     for (int i = 0; i < 3; i++)
                     {
                         for (int j = 0; j < 3; j++)
                         {
                             std::cout << "(" << i << j << ")=" << matrix.vertical_fk[i][j] << " ";
                         };
                         std::cout << std::endl;
                     }
                     std::cout << "------------------------------" << std::endl;
                     std::string filename = getVideo();
                         read_frame(frame_id, filename, frame);
                     cv::Mat *filtered_image = image_filter(frame, matrix.vertical_fk);
                     std::vector<uchar> image_data;
                     convertImage(*filtered_image, image_data);
                     delete filtered_image;

                     std::string s(image_data.begin(), image_data.end());
                     std::cout << "/image/filter2D...Completed" << s.length() << std::endl;
                     res.set_content(s, "image/jpeg");
                 });

        svr.Get("/image/bilateral/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            cv::Mat frame;
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            read_frame(frame_id,filename,frame);
            cv::Mat *filtered_image = bilateralImage(frame);
            convertImage(*filtered_image,image_data);
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });
        svr.Get("/image/style/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            cv::Mat frame;
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            read_frame(frame_id,filename,frame);
            cv::Mat *filtered_image = styleImage(frame);
            convertImage(*filtered_image,image_data);
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });

        svr.Get("/image/sketch/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            cv::Mat frame;
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            read_frame(frame_id,filename,frame);
            cv::Mat *filtered_image = sketchImage(frame);
            convertImage(*filtered_image,image_data);
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });
        svr.Get("/image/sketchColor/:id/:sigma_s/:sigma_r/:shade", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            auto sigma_s = std::stof(req.path_params.at("sigma_s"));
            auto sigma_r = std::stof(req.path_params.at("sigma_r"));
            auto shade = std::stof(req.path_params.at("shade"));

            cv::Mat frame;
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            read_frame(frame_id,filename,frame);
            cv::Mat greyFrame;
            cv::Mat colorFrame;
            sketch(frame,greyFrame,colorFrame,sigma_s,sigma_r,shade);
            convertImage(colorFrame,image_data);
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });

        svr.Get("/image/sketchGrey/:id/:sigma_s/:sigma_r/:shade", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            auto sigma_s = std::stof(req.path_params.at("sigma_s"));
            auto sigma_r = std::stof(req.path_params.at("sigma_r"));
            auto shade = std::stof(req.path_params.at("shade"));

            cv::Mat frame;
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            read_frame(frame_id,filename,frame);
            cv::Mat greyFrame;
            cv::Mat colorFrame;
            sketch(frame,greyFrame,colorFrame,sigma_s,sigma_r,shade);
            convertImage(greyFrame,image_data);
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });
        svr.Get("/image/detailEnhance/:id/:sigma_s/:sigma_r", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            auto sigma_s = std::stof(req.path_params.at("sigma_s"));
            auto sigma_r = std::stof(req.path_params.at("sigma_r"));
            cv::Mat frame;
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            read_frame(frame_id,filename,frame);
            cv::Mat *filtered_image = detailEnhanceImage(frame,sigma_s,sigma_r);
            convertImage(*filtered_image,image_data);
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });
        svr.Get("/image/edgePreserving/:id", [](const auto &req, auto &res)
                {
            auto id = req.path_params.at("id");
            auto frame_id = std::stoi(id);
            cv::Mat frame;
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            read_frame(frame_id,filename,frame);
            cv::Mat *filtered_image = edgePreservingImage(frame);
            convertImage(*filtered_image,image_data);
            std::string s(image_data.begin(), image_data.end());
            res.set_content(s, "image/jpeg"); });
        svr.Get("/video/save", [](const auto &req, auto &res)
                {
            std::cout << "save the video" << std::endl;
            cv::Mat frame;
            std::vector<uchar> image_data;
            std::string filename = getVideo();
            std::string output_filename = "/Users/developer/T9/document/movie/kangli_save.mp4";
            save_video(filename,output_filename);
            res.set_content("Saved." + output_filename, "text/plain"); });

        svr.Get("/image/video/play", [](const httplib::Request& req, httplib::Response& res) {
            // std::string file_path = "/Users/developer/Documents/book/movie/2030_trailer.mp4";
            std::string file_path = getVideo();
            // Use a shared pointer to keep the file open during streaming
            auto file = std::make_shared<std::ifstream>(file_path, std::ios::binary);
            if (!file->is_open()) {
                res.status = 404;
                return;
            }

            // Set content-type and content-length
            file->seekg(0, std::ios::end);
            auto file_size = file->tellg();
            file->seekg(0, std::ios::beg);

            res.set_content_provider(
                file_size,
                "video/mp4",
                [file](size_t offset, size_t length, httplib::DataSink &sink) {
                    file->seekg(offset);
                    std::vector<char> buffer(length);
                    file->read(buffer.data(), length);
                    sink.write(buffer.data(), file->gcount());
                    return true;
                }
            );
        });

        // Set static files
        svr.set_mount_point("/static", config.static_path);
        svr.listen(config.host, config.port);
        return 0; // Returning 0 indicates the program finished successfully
    }

}
//
// Created by developer on 2026-05-22.
//
