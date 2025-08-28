#ifndef OMNI_V2_CLIENT_LOGGER_H
#define OMNI_V2_CLIENT_LOGGER_H
#include <Logger/logger.h>





inline Log::Logger& getClientLogger() {
    static Log::Logger& instance = Log::Logger::getInstance("server_test_logs", Log::FormatType::JSON, 5,true);
    return instance;
}



 
#define server_test_logger getClientLogger()

#endif
