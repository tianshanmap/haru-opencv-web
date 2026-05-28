//
// Created by developer on 2026-05-27.
//
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <utility>
#include <source_location>

#ifndef HARU_OPENCV_WEB_SIMPLE_LOGGER_H
#define HARU_OPENCV_WEB_SIMPLE_LOGGER_H
enum LogLevel { DEBUG, INFO, WARNING, ERROR };
class SimpleLogger {
private:
    std::ofstream logFile;
    LogLevel minimumLevel;

    SimpleLogger() {
        std::cout << "Loading system settings..." << std::endl;
    }

    // Helper to convert enum to string
    std::string levelToString(LogLevel level) {
        switch (level) {
            case DEBUG: return "DEBUG";
            case INFO: return "INFO";
            case WARNING: return "WARNING";
            case ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }
    // Helper to fetch the current system timestamp
    std::string getTimestamp() {
        std::time_t now = std::time(nullptr);
        char buf[20];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        return std::string(buf);
    }
public:
    SimpleLogger(const SimpleLogger&) = delete;
    SimpleLogger& operator=(const SimpleLogger&) = delete;

    // 3. Provide a global static access point
    static SimpleLogger& getInstance() {
        // Thread-safe initialization guaranteed since C++11
        static SimpleLogger instance;
        return instance;
    }

    void configure(const std::string& filename,LogLevel minLevel) {
        this->minimumLevel = minLevel;
        logFile.open(filename, std::ios::app);
    }

    ~SimpleLogger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    // The main logging function
    template <typename... Args>
    void log(LogLevel level, Args... args) {
        if (level < minimumLevel) return; // Filter out lower severity logs

        // std::source_location location = std::source_location::current();
        // std::string filename = std::filesystem::path(location.file_name()).filename().string();
        // std::string logEntry = "[" + getTimestamp() +
        //                        "] [" + levelToString(level) + "] " +
        //                        "[" + filename + ":" + std::to_string(location.line()) + "] ";
        std::string logEntry = "[" + getTimestamp() +
                               "] [" + levelToString(level) + "] ";

        // Print to console
        std::cout << logEntry;
        ([&](const auto& item) {
            std::cout << item << ',';
        }(args), ...);
        std::cout << std::endl;
        // (std::cout << ... << args) << std::endl;
        // std::cout <<  message << std::endl;

        // Save to file
        if (logFile.is_open()) {
            logFile << logEntry;
            ([&](const auto& item) {
                logFile << item << ',';
            }(args), ...);
            logFile << std::endl;
            // logFile << message << std::endl;
        }
    }

    template <typename... Args>
    void debug(Args... args) {
        log(DEBUG, std::forward<Args>(args)...);
    }
    template <typename... Args>
    void info(Args... args) {
        log(INFO, std::forward<Args>(args)...);
    }
    template <typename... Args>
    void warning(Args... args) {
        log(WARNING, std::forward<Args>(args)...);
    }
    template <typename... Args>
    void error(Args... args) {
        log(ERROR, std::forward<Args>(args)...);
    }
};



#endif //HARU_OPENCV_WEB_SIMPLE_LOGGER_H
