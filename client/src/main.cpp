#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <http/httplib.h>
#include <nlohmann/json.hpp>
#include <Logger/logger.h>
#include "client.h"
#include "client_app.h"
#include "client_logger.h"



int main(){


    Client::Client client ("localhost",9000);
    client.test_connection(); 
    client.get("/hello");





   return 0;
}
