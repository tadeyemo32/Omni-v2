#ifndef OMNI_V2_SERVER_H
#define OMNI_V2_SERVER_H

#include <iostream>
#include <http/httplib.h>
#include <string>

namespace Server {

class Server {
private:
    unsigned int port;
    std::string url;
    httplib::SSLServer srv;

public:
    Server();
    Server(std::string l, unsigned int p);
    ~Server();
    
    bool start();  
    void stop();  
    };

} 

#endif
