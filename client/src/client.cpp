#include "client.h"
#include "client_logger.h"
#include <Logger/logger.h>
#include "http/httplib.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json ;
namespace Client {

    Client::Client(std::string name,unsigned int port):client(name,port){
     client_logger.log(std::string("Client Connection Created at: ") + name + " on port " + std::to_string(port),Log::LogType::INFO); 
       this->port = port ;
      this->url = name; 
    }
    Client::Client():client("localhost",8000){
        std::string host = "localhost";
        int port = 8000;
        client_logger.log(std::string("Client Connection Created at: ") + host + " on port " + std::to_string(port),Log::LogType::INFO); 
        test_connection();
    }


    bool Client::test_connection(){
     auto res = client.Get("/health");
      if (res) {
        if(res->status != 200){
         client_logger.log("Test failed to establish connection",Log::LogType::INFO);
            return false;
        }
    
    } else {
        client_logger.log("Test failed to establish connection",Log::LogType::INFO);
        return false;
    }
    client_logger.log("Test connection established",Log::LogType::INFO);
      return true;

    }
    
  json Client::get(const std::string& end_point) {
    auto res = client.Get(end_point);
    json j;

    if (res && res->status == 200) {      
        client_logger.log("JSON Payload Received Succesfully", Log::LogType::INFO);
        try {
            j = json::parse(res->body);
        }catch (const json::parse_error& e) {
            client_logger.log(std::string("JSON parsing failed: ") + e.what(), Log::LogType::ERROR);
        }

    } else {
        client_logger.log("Request failed", Log::LogType::ERROR);
    }

    return j; 
}


json Client::put(const std::string& end_point, const json& payload) {
    std::string body = payload.dump();

    auto res = client.Put(end_point.c_str(), body, "application/json");
    json j;

    if (res && res->status == 200) {
        client_logger.log("PUT request successful. JSON Payload received", Log::LogType::INFO);
        try {
            j = json::parse(res->body);
        } catch (const json::parse_error& e) {
            client_logger.log(std::string("JSON parsing failed: ") + e.what(), Log::LogType::ERROR);
        }
    } else {
        std::string error_msg = "PUT request failed";
        if (res) {
            error_msg += " with status " + std::to_string(res->status);
        }
        client_logger.log(error_msg, Log::LogType::ERROR);
    }

    return j;
}



    Client::~Client(){
        client_logger.log("Client Instance Closed",Log::LogType::INFO);
    }




}














