#ifndef OMNI_V2_CLIENT_H
#define OMNI_V2_CLIENT_H
#include <iostream>
#include <Logger/logger.h>
#include "client_logger.h"
#include "http/httplib.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Client{

class Client {
    private:
    
    httplib::Client client ;
    int port = 8000; 
    std::string url = "localhost";
  
    public:
     Client();
    Client(std::string,unsigned int port);
    bool test_connection();
    json get(const std::string &end_point);
    json put(const std::string& end_point, const json& payload);
    
    ~Client();
        
};







}





















#endif 





