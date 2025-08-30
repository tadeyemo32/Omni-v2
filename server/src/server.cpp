
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
#include "server_auth.h"

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

    srv->Get("/health", [](const httplib::Request&, httplib::Response& res) {
        std::ostringstream oss;
        oss << std::this_thread::get_id();
        server_logger.log("Handling request on thread " + std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id())),
                          Log::LogType::INFO);
        json response_json;
    response_json["status"] = "healthy";
    response_json["message"] = "Server is running!";

    res.status = 200;
    res.set_header("Content-Type", "application/json");
    res.set_content(response_json.dump(), "application/json"); 
        
    });

    server_logger.log("SSL server ready to start...", Log::LogType::INFO);
}

Server::Server() : Server("0.0.0.0", 9000, 10) {}

Server::~Server() {
    stop();
    if (server_thread.joinable()) server_thread.join();
    server_logger.log("Server instance destroyed", Log::LogType::INFO);
}

bool Server::start() {
    server_logger.log("Starting server in background thread...", Log::LogType::INFO);

    server_thread = std::thread([this]() {
        if (!srv->bind_to_port(url, port)) {
            server_logger.log("Failed to bind to port " + std::to_string(port), Log::LogType::ERROR);
            throw std::runtime_error("Failed to bind to port");
        }

        server_logger.log("Server listening on " + url + ":" + std::to_string(port), Log::LogType::INFO);

        if (!srv->listen(url, port, threads)) {
            server_logger.log("Server stopped unexpectedly", Log::LogType::ERROR);
        }
    });

    return true;
}

void Server::stop() {
    if (srv) {
        srv->stop();
        server_logger.log("Server stopped", Log::LogType::INFO);
    }
}

} 
