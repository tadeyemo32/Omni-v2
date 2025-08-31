#include "client.h"
#include "client_logger.h"
#include <Logger/logger.h>
#include "http/httplib.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Client {

Client::Client(std::string name, unsigned int port) 
    : client(name, port), url(name), port(port)
{
    client_logger.log(std::string("Client Connection Created at: ") + name + " on port " + std::to_string(port), Log::LogType::INFO);
    client.enable_server_certificate_verification(false); 
    client.set_connection_timeout(5); 
    client.set_read_timeout(5);
}






json Client::get(const std::string& end_point) {
    auto res = client.Get(end_point.c_str());
   
    if (res && res->status == 200) {
        client_logger.log("GET request successful for endpoint: " + end_point, Log::LogType::INFO);
    } else if (res) {
        client_logger.log("GET request failed for endpoint: " + end_point + " Status: " + std::to_string(res->status), Log::LogType::ERROR);
    } else {
        client_logger.log("GET request failed for endpoint: " + end_point + " - No response", Log::LogType::ERROR);
    }
    
    return json(); 
}



Client::~Client() {
    client_logger.log("Client Instance Closed", Log::LogType::INFO);
}

}
