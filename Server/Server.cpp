#include "Server.h"
#include "../ThreadManager/ThreadManager.h"

void HTTP::Server::accepted(){
    std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";

    session_->receive();
}

void HTTP::Server::accept(){
    std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";

    // session_ = boost::make_shared<HTTP::Session>(Thread::ThreadManager::get_instance().get_io_context());
    // boost::shared_ptr<boost::asio::io_context> sio = boost::make_shared<boost::asio::io_context>(&acceptor_.get_io_context());
    boost::asio::io_context& sio = acceptor_.get_io_context();
    // session_ = boost::make_shared<HTTP::Session>(boost::make_shared<boost::asio::io_context>(sio));
    session_ = boost::make_shared<HTTP::Session>(sio);

    acceptor_.async_accept(
        session_->get_socket(),
        [&](boost::system::error_code const& ec){
            std::cout<<std::this_thread::get_id()<<" "<<__PRETTY_FUNCTION__<<"\n";
            
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