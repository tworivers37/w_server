#include "Session.h"

boost::asio::ip::tcp::socket& HTTP::Session::get_socket(){
    return socket_;
}

void HTTP::Session::received(){
    std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";

    // socket_.get_io_context().post(boost::bind(&HTTP::Session::receive, this));
}

void HTTP::Session::receive(){
    std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";

    boost::asio::async_read(
        socket_,
        boost::asio::buffer(buffer_),
        boost::asio::transfer_at_least(1),
        [&](boost::system::error_code const& ec, std::size_t transferred){
            std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";

            if(ec){
                std::cout<<ec.message()<<"\n";
                return;
            }

            buffer_.resize(transferred);
            std::cout<<"Received : "<<buffer_.data()<<"\n";
            
            buffer_.clear();

            received();
        }
    );
}