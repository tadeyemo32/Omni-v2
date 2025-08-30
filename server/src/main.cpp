#include <iostream>
#include <http/httplib.h>
#include "server.h"
#include "server_logger.h"

int main() {
        Server::Server server("localhost", 9000,10);
       
        server.start();

    while(true) std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}
