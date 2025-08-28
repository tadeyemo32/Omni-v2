#ifndef OMNI_V2_SERVER_LOGGER_H
#define OMNI_V2_SERVER_LOGGER_H
#include <Logger/logger.h>

inline Log::Logger& getServerLogger() {
    static Log::Logger& instance = Log::Logger::getInstance(
        "server_logs", 
        Log::FormatType::JSON,
        5,
        true,
        "../logs"
    );
    return instance;
}

#define server_logger getServerLogger()

#endif
