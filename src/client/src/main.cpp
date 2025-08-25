
#include <iostream>
#include "httplib.h"
#include <nlohmann/json.hpp>
#include "logger/logger.h"

int main() {
    auto &logger = Log::Logger::getInstance();
    logger.log("Server started", Log::INFO); 
  
    return 0;
}
