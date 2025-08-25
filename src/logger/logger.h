
#ifndef OMNI_V2_SRC_LOGGER_H
#define OMNI_V2_SRC_LOGGER_H
#include <iostream>
#include <fstream>
#include <mutex>
#include <chrono>


namespace Log {
enum LogLevel {INFO,DEBUG,WARNING,ERROR,CRITICAL};
class Logger{
    private: 
        std::ofstream file ;
    public:

    explicit Logger(const std::string& filename, std::ios::openmode mode = std::ios::out) {
        std::filesystem::path dirPath = "../logs";      

        if (!std::filesystem::exists(dirPath)) {
            if (std::filesystem::create_directory(dirPath)) {
                std::cout << "Created logs directory: " << dirPath << std::endl;
            } else {
                std::cerr << "Unable to create logs directory: " << dirPath << std::endl;
                throw std::runtime_error("Failed to create logs directory.");
            }
        }
        std::filesystem::path fullLogFilePath = dirPath / filename;

        file.open(fullLogFilePath, mode);

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << fullLogFilePath << std::endl;
            std::cerr << "Current working directory: ";
            std::cerr << std::filesystem::current_path() << std::endl;
            throw std::runtime_error("Failed to open log file: " + fullLogFilePath.string());
        } else {
            std::cout << "Successfully opened file: " <<filename<< std::endl;
        }
    }




     ~Logger() {
            if (file.is_open()) {
                file.close();
            }
        }

        void log(LogLevel level, const std::string& message) {
            if (file.is_open()) {
                file << "[" << static_cast<int>(level) << "] " << message << "\n";
            }
        }
    };


}










#endif 
