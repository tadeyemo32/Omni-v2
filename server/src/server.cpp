#include <nlohmann/json.hpp>
#include "server.h"
#include "server_logger.h"
#include <http/httplib.h>
#include <stdexcept>
#include <thread>
#include <filesystem>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <atomic>
#include "server_auth.h"
#include "server_request_handler.h"

using json = nlohmann::json;
namespace Server {
namespace fs = std::filesystem;

Server::Server(std::string l, unsigned int p, int t_count)
    : url(l), port(p), threads(t_count) 
{
    generate_SSL_Auths();

    srv = std::make_unique<httplib::SSLServer>("runtime_deps/cert.pem","runtime_deps/key.pem");

    server_logger.log(std::string("Server instance created at: ") + url + ":" + std::to_string(port),
                      Log::LogType::INFO);

    if (!srv->is_valid()) {
        server_logger.log("SSL server initialization failed - invalid certificate paths", Log::LogType::ERROR);
        throw std::runtime_error("SSL server initialization failed");
    }

    set_all_end_points(*srv);
    server_logger.log("SSL server ready to start...", Log::LogType::INFO);
}

Server::~Server() {
    stop();
    if (server_thread.joinable()) {
        server_thread.join();
    }
    server_logger.log("Server instance destroyed", Log::LogType::INFO);
}

bool Server::start() {
    server_logger.log("Starting server in background thread...", Log::LogType::INFO);

    server_thread = std::thread([this]() {
        try {
            if (!srv->bind_to_port(url.c_str(), port)) {
                server_logger.log("Failed to bind to port " + std::to_string(port), Log::LogType::ERROR);
                return;
            }

            server_logger.log("Server successfully bound to port " + std::to_string(port), 
                             Log::LogType::INFO);
            
            // Set a reasonable timeout to prevent hanging
            srv->set_read_timeout(5, 0); // 5 seconds
            srv->set_write_timeout(5, 0); // 5 seconds
            
            server_logger.log("Server listening on " + url + ":" + std::to_string(port), 
                             Log::LogType::INFO);
            
            if (!srv->listen_after_bind()) {
                server_logger.log("Server stopped listening", Log::LogType::INFO);
            }
        } catch (const std::exception& e) {
            server_logger.log(std::string("Server thread exception: ") + e.what(), 
                             Log::LogType::ERROR);
        }
    });

    // Give the server a moment to start
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Detach the thread to avoid blocking destruction
    server_thread.detach();
    
    server_logger.log("Server started successfully", Log::LogType::INFO);
    return true;
}

void Server::stop() {
    if (srv) {
        srv->stop();
        server_logger.log("Server stop requested", Log::LogType::INFO);
    }
}
}
