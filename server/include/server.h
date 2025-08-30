#ifndef OMNI_V2_SERVER_H
#define OMNI_V2_SERVER_H

#include <string>
#include <http/httplib.h>

namespace Server {

class Server {
private:
    std::string url;
    unsigned int port;
 std::unique_ptr<httplib::SSLServer> srv;
int threads =1  ;
 std::thread server_thread;
public:
    Server(std::string l, unsigned int p);
    Server();
    Server(std::string l, unsigned int p,int m);
    ~Server();
    
    bool start();
    void stop();
};

}

#endif
