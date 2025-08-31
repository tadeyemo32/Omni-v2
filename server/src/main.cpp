#include <iostream>
#include <http/httplib.h>
#include "server.h"
#include "server_logger.h"
#include <csignal>
#include <atomic>

std::atomic<bool> running{true};

void signalHandler(int signal) {
    running = false;
}

int main() {
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);
    
    try {
        Server::Server server("0.0.0.0", 9000, 10);
       
        if (!server.start()) {
            server_logger.log("Failed to start server", Log::LogType::ERROR);
            return 1;
        }
        
        server_logger.log("Server started. Press Ctrl+C to stop.", Log::LogType::INFO);
        
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
        server.stop();
        server_logger.log("Server shutdown complete", Log::LogType::INFO);
        
    } catch (const std::exception& e) {
        server_logger.log(std::string("Server exception: ") + e.what(), Log::LogType::ERROR);
        return 1;
    }

    return 0;
}
