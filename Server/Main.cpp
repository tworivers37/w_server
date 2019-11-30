#include <iostream>
#include "Server.h"
#include "../ThreadManager/ThreadManager.h"

int main(){
    std::cout<<std::this_thread::get_id()<<" : Main() start\n";

    boost::shared_ptr<boost::asio::io_context> ioc = boost::make_shared<boost::asio::io_context>();
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), 9988);

    boost::shared_ptr<HTTP::Server> server = boost::make_shared<HTTP::Server>(ioc, ep);
    server->start();

    ioc->run();
    
    std::cout<<std::this_thread::get_id()<<" : Main() end\n";

    return 0;
}