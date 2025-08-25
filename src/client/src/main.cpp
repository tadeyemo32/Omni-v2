
#include <iostream>
#include "httplib.h"
#include <nlohmann/json.hpp>
#include "logger/logger.h"

int main() {
    // Initialize Logger singleton (logs to default file)
    auto &logger = Log::Logger::getInstance();
    logger.log("Server started", Log::INFO);

    // Example JSON usage
    nlohmann::json exampleJson;
    exampleJson["message"] = "Hello, world!";
    std::cout << exampleJson.dump(4) << std::endl;

    // Example HTTP server setup (optional)
    // httplib::Server svr;
    // svr.Get("/", [](const httplib::Request&, httplib::Response& res){
    //     res.set_content("Hello from server!", "text/plain");
    // });
    // svr.listen("localhost", 8080);

    return 0;
}
