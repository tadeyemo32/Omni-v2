#ifndef OMNI_V2_SRC_LOGGER_H
#define OMNI_V2_SRC_LOGGER_H

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <stdexcept>

using json = nlohmann::json;

namespace Log {

    std::string current_time() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm local_tm = *std::localtime(&now_time_t);

        std::ostringstream oss;
        oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    enum log_type { INFO, DEBUG, WARNING, ERROR, CRITICAL, UNKNOWN };

    std::string logTypeToString(log_type &t) {
        std::string logT;
        switch (t) {
            case INFO:     logT = "Info";     break;
            case DEBUG:    logT = "Debug";    break;
            case WARNING:  logT = "Warning";  break;
            case ERROR:    logT = "Error";    break;
            case CRITICAL: logT = "Critical"; break;
            case UNKNOWN:  logT = "Unknown";  break;
            default:       logT = "Undefined type"; break;
        }
        return logT;
    }

    namespace ns {
        void to_Json(json &j, const std::string &m, log_type &t) {
            std::string logT = logTypeToString(t);
            j = json{
                {"Log Type", logT},
                {"Log", m},
                {"Timestamp", current_time()}
            };
        }
    }

    class Logger {
    private:
        std::ofstream file;

        Logger() {
            std::filesystem::path dirPath = "../logs";

            if (!std::filesystem::exists(dirPath)) {
                if (std::filesystem::create_directory(dirPath)) {
                    std::cout << "[" << current_time() << "] Created logs directory: logs" << std::endl;
                } else {
                    throw std::runtime_error("Failed to create logs directory.");
                }
            }

            std::filesystem::path fullLogFilePath = dirPath / "log.json";
            file.open(fullLogFilePath, std::ios::out | std::ios::app);

            if (!file.is_open()) {
                throw std::runtime_error("Failed to open log file: " + fullLogFilePath.string());
            } else {
                std::cout << "[" << current_time() << "] Successfully opened log file" << std::endl;
                log("Client Started", INFO);
            }
        }

    public:
        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;

        static Logger &getInstance() {
            static Logger instance;
            return instance;
        }

        void log(const std::string &message, log_type type) {
            if (file.is_open()) {
                json j;
                ns::to_Json(j, message, type);
                file << std::setw(4) << j << std::endl;
                std::cout << "[" << current_time() << "] -> [" << logTypeToString(type) << "] Log Generated Successfully\n";
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

