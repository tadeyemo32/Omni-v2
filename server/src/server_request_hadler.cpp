#include "server.h"
#include "server_logger.h"
#include "server_request_handler.h"
#include "http/httplib.h"
#include "nlohmann/json.hpp"

using namespace httplib;
using json = nlohmann::json;
namespace Server{

void  set_all_end_points(SSLServer& s){
    
      set_health_endPoint(s);
      set_root(s);
}




    void set_health_endPoint(SSLServer& server){
        server.Get("/health",[](const Request&,Response& res ){
         res.set_header("Content-Type","application/json");
         json j;
         j["status"] = "healthy";                
         j["version"] = "1.0.0";             
         j["message"] = "All systems nominal";

         res.status = 200;
        res.set_header("Content-Type", "application/json");
         res.set_content(j.dump(4), "application/json");

             });


    }

    void set_root(SSLServer& s){
        s.Get("/",[](const Request&,Response& res){
        json j;

        j["name"]="Omni Server";
        j["version"]="1.0.0";
        j["description"]="SSL server";
        j["endpoints"]= {"/health","/stock"};

        res.status = 200;
        res.set_header("Content-Type","application/json");
        res.set_content(j.dump(4),"appplication/json");
     });       
        
    }


}



