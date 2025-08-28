#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <http/httplib.h>
#include <Logger/logger.h>
#include "server_tests_logger.h"



int main() {
    std::cout << "=== SSL Server Test ===" << std::endl;
    server_test_logger.log("Server Test Instance created Logger Active...",Log::LogType::INFO);



    try {
        // Create SSL server with certificate and key
        httplib::SSLServer server("../runtime deps/cert.pem", "../runtime deps/key.pem");
        
        if (!server.is_valid()) {
            std::cerr << "Server initialization failed!" << std::endl;
           server_test_logger.log("Server Initialization failed",Log::LogType::ERROR); 
            return 1;
        }




        server.Get("/health", [](const httplib::Request&, httplib::Response& res) {
            res.set_content("{\"status\": \"healthy\", \"message\": \"SSL Server Test is running!\"}", "application/json");
        });
       



        server.Get("/test", [](const httplib::Request&, httplib::Response& res) {
            res.set_content("{\"test\": \"success\", \"ssl\": true}", "application/json");
        });



        
        if (!server.bind_to_port("localhost", 9001)) {
            std::cerr << "Failed to bind to port 9001!" << std::endl;
             server_test_logger.log("Failed to bind to port 9001",Log::LogType::ERROR); 
            return 1;
        }
        
        server.listen_after_bind();
        
    } catch (const std::exception& e) {

    server_test_logger.log(std::string("Server failed: ") + e.what(), Log::LogType::ERROR);
        return 1;
    }
   


    server_test_logger.log(std::string("Server Ended "), Log::LogType::INFO);
    return 0;
}
