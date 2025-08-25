
#ifndef OMNI_V2_SRC_LOGGER_H
#define OMNI_V2_SRC_LOGGER_H


#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <stdexcept>
namespace Log{
class Logger {
private:
    std::ofstream file;

    // Helper to get current time as a formatted string
    std::string current_time() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm local_tm = *std::localtime(&now_time_t);

        std::ostringstream oss;
        oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

public:
    explicit Logger(const std::string& filename, std::ios::openmode mode = std::ios::out) {
        std::filesystem::path dirPath = "../logs";

        // Ensure logs directory exists
        if (!std::filesystem::exists(dirPath)) {
            if (std::filesystem::create_directory(dirPath)) {
                std::cout << "[" << current_time() << "] "
                          << "Created logs directory: logs" << std::endl;
            } else {
                std::cerr << "Unable to create logs directory: " << dirPath << std::endl;
                throw std::runtime_error("Failed to create logs directory.");
            }
        }

        // Build full log file path
        std::filesystem::path fullLogFilePath = dirPath / filename;

        // Try to open the log file
        file.open(fullLogFilePath, mode);

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << fullLogFilePath << std::endl;
            std::cerr << "Current working directory: "
                      << std::filesystem::current_path() << std::endl;
            throw std::runtime_error("Failed to open log file: " + fullLogFilePath.string());
        } else {
         std::cout << "[" << current_time() << "] "
                      << "Successfully opened file: " << filename << std::endl;
        }
    }

    void log(const std::string& message) {
        if (file.is_open()) {
            file << "[" << current_time() << "] " << message << std::endl;
        }
    }

    ~Logger() {
        if (file.is_open()) {
            file.close();
        }
    }
};

}
#endif 
