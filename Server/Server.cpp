#include "Server.h"

unsigned int HTTP::Server::get_session_index(){
    if(session_index_ > 4) session_index_ = 0;
    return session_index_++ % 4;
}

void HTTP::Server::accepted(){
    std::cout<<std::this_thread::get_id()<<" "<<__PRETTY_FUNCTION__<<"\n";

    // acceptor_.get_io_context().post(boost::bind(&HTTP::Server::accept, this));

    session_->receive();
}

void HTTP::Server::accept(){
    std::cout<<std::this_thread::get_id()<<" "<<__PRETTY_FUNCTION__<<"\n";

    // session_ = boost::make_shared<HTTP::Session>(session_ioc_[get_session_index()]);
    session_ = boost::make_shared<HTTP::Session>(acceptor_.get_io_context());

    acceptor_.async_accept(
        session_->get_socket(),
        [&](boost::system::error_code const& ec){
            std::cout<<std::this_thread::get_id()<<" "<<__PRETTY_FUNCTION__<<"\n";
            accepted();
        }
    );
}

void HTTP::Server::start(){
    std::cout<<std::this_thread::get_id()<<" "<<__PRETTY_FUNCTION__<<"\n";

    for(int i=0; i<session_ioc_.size(); ++i)
        tg_.create_thread(
            [&, i](){
                session_ioc_[i].run();
            }
        );

    accept();

    tg_.join_all();
}

void HTTP::Server::stop(){

}