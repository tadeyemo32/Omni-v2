#ifndef OMNI_V2_SERVER_H
#define OMNI_V2_SERVER_H

#include <string>
#include <http/httplib.h>

namespace Server {

class Server {
private:
    std::string url;
    unsigned int port;
    httplib::SSLServer srv;

public:
    Server(std::string l, unsigned int p);
    Server();
    ~Server();
    
    bool start();
    void stop();
};

}

#endif