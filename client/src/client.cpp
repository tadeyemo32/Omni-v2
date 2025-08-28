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
    test_connection();
}


Client::Client() 
    : client("localhost", 9000), url("localhost"), port(9000)
{
    client_logger.log(std::string("Client Connection Created at: localhost on port 9000"), Log::LogType::INFO);
    client.enable_server_certificate_verification(false); 
    client.set_connection_timeout(5);
    client.set_read_timeout(5);
}

bool Client::test_connection() {
    auto res = client.Get("/health");
    if (res) {
        if(res->status == 200) {
            std::string content_type = res->get_header_value("Content-Type");
            if (content_type.find("application/json") != std::string::npos) {
                try {
                    json j = json::parse(res->body);
                    client_logger.log("Test connection established successfully with JSON response", Log::LogType::INFO);
                    return true;
                } catch (const json::parse_error& e) {
                    client_logger.log("Test connection established but JSON parsing failed: " + std::string(e.what()), Log::LogType::ERROR);
                    return true;
                }
            } else {
                client_logger.log("Test connection established with non-JSON response: " + content_type, Log::LogType::INFO);
                return true;
            }
        } else {
            client_logger.log("Test failed - non-200 status: " + std::to_string(res->status), Log::LogType::ERROR);
            return false;
        }
    } else {
        client_logger.log("Test failed to establish connection: " , Log::LogType::ERROR);
        return false;
    }
}

json Client::parse_response(const httplib::Result& res, const std::string& endpoint) {
    json j;
    
    if (!res) {
        j = {
            {"error", "no_response"},
            {"message", "No response from server"},
            {"endpoint", endpoint}
        };
        return j;
    }
    
    std::string content_type = res->get_header_value("Content-Type");
    
    if (content_type.find("application/json") != std::string::npos) {
        try {
            j = json::parse(res->body);
        } catch (const json::parse_error& e) {
            j = {
                {"error", "json_parse_error"},
                {"message", e.what()},
                {"raw_response", res->body},
                {"content_type", content_type},
                {"endpoint", endpoint},
                {"status", res->status}
            };
        }
    } else{ 
        j = {
            {"status", res->status},
            {"content_type", content_type},
            {"body", res->body},
            {"endpoint", endpoint}
        };
    }
    
    return j;
}




json Client::get(const std::string& end_point) {
    auto res = client.Get(end_point.c_str());
    json j = parse_response(res, end_point);
    
    if (res && res->status == 200) {
        client_logger.log("GET request successful for endpoint: " + end_point, Log::LogType::INFO);
    } else if (res) {
        client_logger.log("GET request failed for endpoint: " + end_point + " Status: " + std::to_string(res->status), Log::LogType::ERROR);
    } else {
        client_logger.log("GET request failed for endpoint: " + end_point + " - No response", Log::LogType::ERROR);
    }
    
    return j; 
}



Client::~Client() {
    client_logger.log("Client Instance Closed", Log::LogType::INFO);
}

}
