#include <iostream>
#include "httplib.h"
#include <nlohmann/json.hpp>
#include <logger/logger.h>
int main(){
 using namespace Log;
        Logger logger("client_logs.json");
   


        logger.log("Something shoudl be at end ",DEBUG);
    return 0;
}
