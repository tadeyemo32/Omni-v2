#include <iostream>
#include <http/httplib.h>
#include <nlohmann/json.hpp>
#include "client.h"
#include "client_logger.h"

using json = nlohmann::json;

int main() {
    try {
        Client::Client client("localhost", 9000);
        
        std::cout << "Testing connection to server..." << std::endl;
        if (!client.test_connection()) {
            std::cerr << "Failed to connect to server" << std::endl;
            return 1;
        }
        
        std::cout << "Connection successful. Making GET request to /health..." << std::endl;
        json j = client.get("/health");
        
        if (j.contains("error")) {
            std::cerr << "Error in response: " << j.dump(4) << std::endl;
            
            if (j["error"] == "json_parse_error" && j.contains("raw_response")) {
                std::cout << "Raw server response: " << j["raw_response"] << std::endl;
            }
            return 1;
        }
        
        std::cout << "Server response:" << std::endl;
        std::cout << j.dump(4) << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
