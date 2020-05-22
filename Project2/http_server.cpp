#include "httplib.h"

void HelloWorld(const httplib::Requset &req, httplib::Response &rsp)
{
std::cout << "method:"<<req.method<<std:endl;
std::cout << "path:"<<req.method<<std:endl;
std::cout << "body:"<<req.method<<std:endl;
rsp.status =200;
rsp.body="<html><body><h1>HelloWord</h1></body></html>";
rsp.set_header("Content-Type","text/html"); 

return ;
}

int main()
{
httplib::Server server;
server.Get("/helloworld",HelloWord);
server.listen("0.0.0.0",9000);
return 0;
}

