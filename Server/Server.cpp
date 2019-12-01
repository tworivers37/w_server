#include "Server.h"
#include "../ThreadManager/ThreadManager.h"

void HTTP::Server::accepted(){
    std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";

    boost::asio::post(
        session_->get_socket().get_io_context(),
        boost::bind(&HTTP::Session::receive, session_)
    );

    accept();
}

void HTTP::Server::accept(){
    std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";
    
    session_ = boost::make_shared<HTTP::Session>(Thread::ThreadManager::get_instance().get_io_context());

    acceptor_.async_accept(
        session_->get_socket(),
        [&](boost::system::error_code const& ec){
            std::cout<<std::this_thread::get_id()<<" "<<__PRETTY_FUNCTION__<<"\n";
            
            std::cout<<"session local : "<<session_->get_socket().local_endpoint()<<"\n";
            std::cout<<"session remote : "<<session_->get_socket().remote_endpoint()<<"\n";

            if(ec){
                std::cout<<"accept lambda ec : "<<ec.message()<<" "<<ec.value()<<"\n";
                return;
            }

            accepted();

        }
    );
}

void HTTP::Server::init(){
    acceptor_.open(server_endpoint_.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(server_endpoint_);
    acceptor_.listen(1024);
}

void HTTP::Server::start(){
    std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";
    init();
    accept();
}

void HTTP::Server::stop(){

}