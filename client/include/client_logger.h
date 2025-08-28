#ifndef OMNI_V2_CLIENT_LOGGER_H
#define OMNI_V2_CLIENT_LOGGER_H
#include <Logger/logger.h>




inline Log::Logger& getClientLogger() {
    static Log::Logger& instance = Log::Logger::getInstance(
        "client_logs",
        Log::FormatType::JSON,
        5,
        true,
        "../logs"
    );
    return instance;
}


 
#define client_logger getClientLogger()

#endif
