#include <iostream>
#include "Server.h"

int main(){
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), 9900);
    boost::asio::io_context ioc;
    HTTP::Server server(ioc, ep);
    server.start();
    ioc.run();
    
    return 0;
}