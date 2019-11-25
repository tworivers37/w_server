#include "Server.h"
#include "../ThreadManager/ThreadManager.h"

void HTTP::Server::accepted(){
    std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";

    session_->receive();
}

void HTTP::Server::accept(){
    std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";

    acceptor_.open(server_endpoint_.protocol());
    acceptor_.bind(server_endpoint_);
    acceptor_.listen(1024 * 1024);

    session_ = boost::make_shared<HTTP::Session>(Thread::ThreadManager::get_instance().get_io_context());

    acceptor_.async_accept(
        session_->get_socket(),
        [&](boost::system::error_code const& ec){
            std::cout<<std::this_thread::get_id()<<" "<<__PRETTY_FUNCTION__<<"\n";
            
            std::cout<<"session local : "<<session_->get_socket().local_endpoint()<<"\n";
            std::cout<<"session remote : "<<session_->get_socket().remote_endpoint()<<"\n";

            if(ec){
                std::cerr<<"ec : "<<ec.message()<<" "<<ec.value()<<"\n";
                return;
            }

            accepted();
        }
    );
}

void HTTP::Server::start(){
    std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";
    accept();
}

void HTTP::Server::stop(){

}