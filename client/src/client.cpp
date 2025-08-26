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
      this->location = name; 
    }
    Client::Client():client("localhost",8000){
        std::string host = "localhost";
        int port = 8000;
        client_logger.log(std::string("Client Connection Created at: ") + host + " on port " + std::to_string(port),Log::LogType::INFO); 
    }

    void Client::test_connection(){
     auto res = client.Get("/hello");
      if (res) {
        std::cout << "Status: " << res->status << "\n";
        std::cout << "Body: " << res->body << "\n";
    } else {
        std::cout << "Request failed\n";
    }

    }
    
  json Client::get(const std::string& end_point) {
    auto res = client.Get(end_point);
    json j;

    if (res && res->status == 200) {      
        client_logger.log("JSON Payload Received Succesfully", Log::LogType::INFO);
        try {
            j = json::parse(res->body);         } catch (const json::parse_error& e) {
            client_logger.log(std::string("JSON parsing failed: ") + e.what(), Log::LogType::ERROR);
        }

    } else {
        client_logger.log("Request failed", Log::LogType::ERROR);
    }

    return j; 
}



    Client::~Client(){
        client_logger.log("Client Instance Closed",Log::LogType::INFO);
    }




}














