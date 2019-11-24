#include <iostream>
#include "Server.h"
#include "../ThreadManager/ThreadManager.h"

int main(){
    std::cout<<std::this_thread::get_id()<<" : Main()\n";

    // auto ioc = Thread::ThreadManager::get_instance().get_io_context();
    boost::shared_ptr<boost::asio::io_context> ioc = boost::make_shared<boost::asio::io_context>();
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), 9988);

    HTTP::Server server(ioc, ep);
    server.start();

    ioc->run();
    
    return 0;
}