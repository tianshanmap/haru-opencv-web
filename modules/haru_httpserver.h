//
// Created by developer on 2026-05-27.
//
#include "../include/httplib.hpp"
#include "simple_logger.h"

#ifndef HARU_OPENCV_WEB_HARU_HTTPSERVER_H
#define HARU_OPENCV_WEB_HARU_HTTPSERVER_H
namespace haru {
    int webMain(YamlConfig &config);
    class HaruHttpServer {
    private:
        httplib::Server *svr;
        std::map<std::string,std::string> mapping;
    public:
        HaruHttpServer(httplib::Server *svr) {
            this->svr = svr;
        };
        void add_mapping(std::string key,std::string value) {
            this->mapping[key] = value;
        }
        std::map<std::string,std::string> get_mappings() {
            return this->mapping;
        }
        void Get(const std::string &pattern, std::function<void(const httplib::Request &, httplib::Response &)> handler) {
            this->svr->Get(pattern, handler);
            add_mapping(pattern,"GET");
        }
        void Post(const std::string &pattern, std::function<void(const httplib::Request &, httplib::Response &)> handler) {
            this->svr->Post(pattern, handler);
            add_mapping(pattern,"POST");
        }
        void Options(const std::string &pattern, std::function<void(const httplib::Request &, httplib::Response &)> handler) {
            this->svr->Options(pattern, handler);
            add_mapping(pattern,"OPTIONS");
        }
        void set_mount_point(std::string &&path, std::string &dir) {
            this->svr->set_mount_point(path, dir);
        }
        void start(std::string &host, int port) {
            SimpleLogger &logger = SimpleLogger::getInstance();
            logger.info("List of the supported endpoint=>");
            for (auto &item : mapping) {
                logger.info("       " + item.first + " => " + item.second);
            }
            this->svr->listen(host, port);
        }
    };
}
#endif //HARU_OPENCV_WEB_HARU_HTTPSERVER_H
