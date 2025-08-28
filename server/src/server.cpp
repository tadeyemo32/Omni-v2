#include "server.h"
#include "server_logger.h"
#include <http/httplib.h>
#include <stdexcept>
#include <thread>
#include <filesystem>

namespace Server {

Server::Server(std::string l, unsigned int p)
    : url(l), port(p), srv("../bin/runtime deps/cert.pem", "../bin/runtime deps/key.pem")
{
    server_logger.log(std::string("Server instance created at: ") + url + ":" + std::to_string(port), Log::LogType::INFO);
    
    if (!srv.is_valid()) {
        server_logger.log("SSL server initialization failed - invalid certificate paths", Log::LogType::ERROR);
        throw std::runtime_error("SSL server initialization failed");
    }
    
    srv.Get("/health", [](const httplib::Request&, httplib::Response& res) {
        res.status = 200;
        res.set_header("Content-Type", "application/json");      
        res.set_content("{\"status\": \"healthy\", \"message\": \"Server is running!\"}", "application/json");
    });
    
    server_logger.log("Starting SSL server...", Log::LogType::INFO);
    
    if (!srv.bind_to_port(url, port)) {
        server_logger.log("Failed to bind to port " + std::to_string(port), Log::LogType::ERROR);
        throw std::runtime_error("Failed to bind to port");
    }
    
    server_logger.log("Server listening on " + url + ":" + std::to_string(port), Log::LogType::INFO);
}

Server::Server()
    : url("localhost"), port(9000), srv("../bin/runtime deps/cert.pem", "../bin/runtime deps/key.pem")
{
    server_logger.log(std::string("Server instance created at: ") + url + ":" + std::to_string(port), Log::LogType::INFO);
    
    if (!srv.is_valid()) {
        server_logger.log("SSL server initialization failed - invalid certificate paths", Log::LogType::ERROR);
        throw std::runtime_error("SSL server initialization failed");
    }
    
    srv.Get("/health", [](const httplib::Request&, httplib::Response& res) {
        res.status = 200;
        res.set_header("Content-Type", "application/json");  
        res.set_content("{\"status\": \"healthy\", \"message\": \"Server is running!\"}", "application/json");
    });
    
    server_logger.log("Starting SSL server...", Log::LogType::INFO);
    
    if (!srv.bind_to_port(url, port)) {
        server_logger.log("Failed to bind to port " + std::to_string(port), Log::LogType::ERROR);
        throw std::runtime_error("Failed to bind to port");
    }
    
    server_logger.log("Server listening on " + url + ":" + std::to_string(port), Log::LogType::INFO);
}



Server::~Server() {
    srv.stop();
    server_logger.log("Server instance destroyed", Log::LogType::INFO);
}

bool Server::start() {
    server_logger.log("Starting server listening...", Log::LogType::INFO);
    return srv.listen_after_bind();
}

void Server::stop() {
    srv.stop();
    server_logger.log("Server stopped", Log::LogType::INFO);
}

}
