#ifndef SERVER_TESTS_LOGGER_H
#define SERVER_TESTS_LOGGER_H
#include <Logger/logger.h>

inline Log::Logger& getServerTestLogger() {
    static Log::Logger& instance = Log::Logger::getInstance(
        "server_test_logs",
        Log::FormatType::JSON,
        5,
        true,
        "../../logs"
    );
    return instance;
}

#define server_test_logger getServerTestLogger()

#endif
