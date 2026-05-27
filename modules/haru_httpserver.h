//
// Created by developer on 2026-05-27.
//
#include "../include/httplib.hpp"

#ifndef HARU_OPENCV_WEB_HARU_HTTPSERVER_H
#define HARU_OPENCV_WEB_HARU_HTTPSERVER_H
namespace haru {
    int webMain(YamlConfig &config);
    class HaruHttpServer {
    private:
        httplib::Server *svr;
    public:
        HaruHttpServer(httplib::Server *svr) {
            this->svr = svr;
        };
        void Get(const std::string &pattern, std::function<void(const httplib::Request &, httplib::Response &)> handler) {
            this->svr->Get(pattern, handler);
        }
        void Post(const std::string &pattern, std::function<void(const httplib::Request &, httplib::Response &)> handler) {
            this->svr->Post(pattern, handler);
        }
        void Options(const std::string &pattern, std::function<void(const httplib::Request &, httplib::Response &)> handler) {
            this->svr->Options(pattern, handler);
        }
    };
}
#endif //HARU_OPENCV_WEB_HARU_HTTPSERVER_H
