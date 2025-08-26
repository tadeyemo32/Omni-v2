#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <http/httplib.h>
#include <nlohmann/json.hpp>
#include <Logger/logger.h>
#include "server.h"

using json = nlohmann::json;

int main(){
    std::cout<<"Server Starting..\n";

   httplib::Server svr;

  svr.Get("/hello", [](const httplib::Request&, httplib::Response& res) {

        json j ;
        j["message"] = "Hello from local server test succesfull";
        res.set_content(j.dump(4),"application/json");
    
});

    std::cout << "Server running on http://localhost:9000\n";
    svr.listen("localhost", 9000);
    
   return 0;
}
