#include <iostream>
#include <http/httplib.h>
#include "server.h"
#include "server_logger.h"

int main() {
    try {
        std::cout << "Starting SSL Server on localhost:9000..." << std::endl;
        Server::Server server("localhost", 9000);
        
        std::cout << "Server initialized. Starting listening..." << std::endl;
        if (server.start()) {
            std::cout << "Server started successfully. Press Ctrl+C to stop." << std::endl;
            while (true) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        } else {
            std::cerr << "Failed to start server listening" << std::endl;
            return 1;
        }
        
    } catch (const std::exception& e) {
        server_logger.log(std::string("Server failed: ") + e.what(), Log::LogType::ERROR);
        std::cerr << "Server failed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
