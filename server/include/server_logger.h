#ifndef OMNI_V2_SERVER_LOGGER_H
#define OMNI_V2_SERVER_LOGGER_H
#include <Logger/logger.h>





inline Log::Logger& getClientLogger() {
    static Log::Logger& instance = Log::Logger::getInstance("server_logs", Log::FormatType::JSON, 5,true);
    return instance;
}



 
#define server_logger getClientLogger()

#endif

