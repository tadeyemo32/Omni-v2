#ifndef OMNI_V2_SERVER_REQUEST_HANDLER_H
#define OMNI_V2_SERVER_REQUEST_HANDLER_H
#include <http/httplib.h>


namespace Server{



    void set_health_endPoint(httplib::SSLServer& server);
    
    void set_all_end_points(httplib::SSLServer& s);
       void set_root(httplib::SSLServer& s);



}





#endif 
