#include <iostream>
#include <http/httplib.h>
#include <nlohmann/json.hpp>
#include <Logger/logger.h>

using json = nlohmann::json;

int main() {
    std::cout << "=== SSL Client Test ===" << std::endl;
    
    try {
        httplib::SSLClient cli("localhost", 9001);         
        cli.enable_server_certificate_verification(false);
        
        cli.set_connection_timeout(5);
        cli.set_read_timeout(5);
        
        std::cout << "Testing connection to test server on port 9001..." << std::endl;
        
        std::vector<std::string> endpoints = {"/health", "/test"};
        
        for (const auto& endpoint : endpoints) {
            std::cout << "\nTesting endpoint: " << endpoint << std::endl;
            
            auto res = cli.Get(endpoint.c_str());
            
            if (res) {
                std::cout << "✓ Status: " << res->status << std::endl;
                std::cout << "Response: " << res->body << std::endl;
                
                if (res->get_header_value("Content-Type").find("application/json") != std::string::npos) {
                    try {
                        json j = json::parse(res->body);
                        std::cout << "Parsed JSON: " << j.dump(2) << std::endl;
                    } catch (const std::exception& e) {
                        std::cout << "JSON parse error: " << e.what() << std::endl;
                    }
                }
            } else {
                auto err = res.error();
                std::cout << "✗ Error: " << httplib::to_string(err) << std::endl;
                std::cout << "Make sure the test server is running on port 9001!" << std::endl;
                return 1;
            }
        }
        
        std::cout << "\n✓ All tests passed!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
