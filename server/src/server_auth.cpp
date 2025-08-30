#include "server_logger.h"
#include <filesystem>
#include <cstdlib>
#include <sstream>
#include "server_auth.h"


namespace fs = std::filesystem;







 void generate_SSL_Auths() {
    const std::string keyPath = "runtime_deps/key.pem";
    const std::string certPath = "runtime_deps/cert.pem";

    if (fs::exists(keyPath) && fs::exists(certPath)) {
        server_logger.log("SSL Certs found", Log::LogType::INFO);
        return;
    }

    server_logger.log("SSL Certs missing. Generating self-signed certificate...", Log::LogType::INFO);

    fs::create_directories("runtime_deps");

    std::string keyCmd = "openssl genrsa -out " + keyPath + " 2048";
    if (system(keyCmd.c_str()) != 0) {
        server_logger.log("Failed to generate key.pem", Log::LogType::ERROR);
        return;
    }

    std::string certCmd = "openssl req -new -x509 -key " + keyPath + " -out " + certPath +
                          " -days 365 -subj \"/C=US/ST=State/L=City/O=Organization/OU=Unit/CN=localhost\"";
    if (system(certCmd.c_str()) != 0) {
        server_logger.log("Failed to generate cert.pem", Log::LogType::ERROR);
        return;
    }

    server_logger.log("Self-signed SSL certificate generated successfully!", Log::LogType::INFO);
}
