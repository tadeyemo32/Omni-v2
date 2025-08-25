#include <iostream>
#include "httplib.h"
#include <nlohmann/json.hpp>
#include "logger/logger.h"




int main(){
    std::cout<<"Server Starting..\n";
        Log::Logger logger("server_logs.json");

    return 0;
}
