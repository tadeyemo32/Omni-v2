
#include "server.h"
#include "server_logger.h"
#include <http/httplib.h>
#include <stdexcept>
#include <thread>

namespace Server {

    
Server::Server(std::string l, unsigned int p)
    : url(l), port(p), srv("./runtime deps/cert.pem", "./runtime deps/key.pem")
{
    server_logger.log(std::string("Server instance created at: ") + url + ":" + std::to_string(port), Log::LogType::INFO);
    
  
    
    server_logger.log("Starting SSL server...", Log::LogType::INFO);
    
    if (!srv.bind_to_port(url, port)) {
        server_logger.log("Failed to bind to port " + std::to_string(port), Log::LogType::ERROR);
        return;
    }
    
    server_logger.log("Server listening on " + url + ":" + std::to_string(port), Log::LogType::INFO);
}

Server::Server()
    : url("localhost"), port(9000), srv("./runtime deps/cert.pem", "./runtime deps/key.pem")
{
    server_logger.log(std::string("Server instance created at: ") + url + ":" + std::to_string(port), Log::LogType::INFO);
    
    srv.Get("/health", [](const httplib::Request&, httplib::Response& res) {
            res.status = 200;
        res.set_content("Server is running!", "text/plain");
    });
    
    server_logger.log("Starting SSL server...", Log::LogType::INFO);
    
    // Check if server can bind to port
    if (!srv.bind_to_port(url, port)) {
        server_logger.log("Failed to bind to port " + std::to_string(port), Log::LogType::ERROR);
        return;
    }
    
    server_logger.log("Server listening on " + url + ":" + std::to_string(port), Log::LogType::INFO);
}



Server::~Server() {
    srv.stop();
    server_logger.log("Server instance destroyed", Log::LogType::INFO);
}

bool Server::start() {
    return srv.listen(url, port);
}

void Server::stop() {
    srv.stop();
    server_logger.log("Server stopped", Log::LogType::INFO);
}




}
