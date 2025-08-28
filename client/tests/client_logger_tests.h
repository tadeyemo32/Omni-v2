#ifndef CLIENT_TESTS_LOGGER_H
#define CLIENT_TESTS_LOGGER_H
#include <Logger/logger.h>

inline Log::Logger& getClientTestLogger() {
    static Log::Logger& instance = Log::Logger::getInstance(
        "client_test_logs",
        Log::FormatType::JSON,
        5,
        true,
        "../../logs"
    );
    return instance;
}

#define client_test_logger getClientTestLogger()

#endif
