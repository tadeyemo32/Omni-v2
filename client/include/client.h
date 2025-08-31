#ifndef OMNI_V2_CLIENT_H
#define OMNI_V2_CLIENT_H
#include <iostream>
#include <Logger/logger.h>
#include "client_logger.h"
#include "http/httplib.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Client {

class Client {
private:
    httplib::SSLClient client;
    int port;
    std::string url;
    
    json parse_response(const httplib::Result& res, const std::string& endpoint);
  
public:
    Client() = delete;
    Client(std::string url, unsigned int port);
    bool test_connection();
    json get(const std::string &end_point);
    json put(const std::string& end_point, const json& payload);
    
    ~Client();
};

}

#endif
