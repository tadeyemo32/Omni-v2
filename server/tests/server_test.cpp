#include <iostream>
#include <http/httplib.h>
#include <Logger/logger.h>
#include "server_tests_logger.h"

int main() {
    std::cout << "=== SSL Server Test ===" << std::endl;
    server_test_logger.log("Server Test Instance created Logger Active...", Log::LogType::INFO);

    try {
        httplib::SSLServer server("../bin/runtime deps/cert.pem", "../bin/runtime deps/key.pem");
        
        if (!server.is_valid()) {
            std::cerr << "Server initialization failed!" << std::endl;
            server_test_logger.log("Server Initialization failed", Log::LogType::ERROR); 
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
            server_test_logger.log("Failed to bind to port 9001", Log::LogType::ERROR); 
            return 1;
        }
        
        std::cout << "Server listening on port 9001..." << std::endl;
        server_test_logger.log("Server listening on port 9001", Log::LogType::INFO);
        server.listen_after_bind();
        
    } catch (const std::exception& e) {
        server_test_logger.log(std::string("Server failed: ") + e.what(), Log::LogType::ERROR);
        std::cerr << "Server failed: " << e.what() << std::endl;
        return 1;
    }

    server_test_logger.log("Server Ended", Log::LogType::INFO);
    return 0;
}