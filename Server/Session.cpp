#include "Session.h"

boost::asio::ip::tcp::socket& HTTP::Session::get_socket(){
    return socket_;
}

void HTTP::Session::written(boost::system::error_code const& ec, std::size_t transferred){
    std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";

    if(ec){
        std::cout<<"ec : "<<ec.message()<<"\n";
        socket_.close();
        return;
    }

    socket_.close();
    return;
}

void HTTP::Session::write(){
    std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";
    std::string send_data = "HTTP/1.1 200 OK\r\n\r\nServer TEST";
    
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(send_data),
        boost::asio::transfer_all(),
        boost::bind(
            &HTTP::Session::written,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void HTTP::Session::received(boost::system::error_code const& ec, std::size_t transferred){
    std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";

    if(ec){
        std::cout<<"ec : "<<ec.message()<<"\n";
        socket_.close();

        return;
    }

    std::cout<<"\n------------------------- Received -------------------------\n";
    std::cout<<buffer_.data()<<"\n";

    buffer_.clear();

    boost::asio::post(
        socket_.get_io_context(),
        boost::bind(
            &HTTP::Session::write,
            shared_from_this()
        )
    );

    this->receive();
}

void HTTP::Session::receive(){
    std::cout<<std::this_thread::get_id()<<" : "<<__PRETTY_FUNCTION__<<"\n";

    buffer_.resize(1024 * 1024);

    boost::asio::async_read(
        socket_,
        boost::asio::buffer(buffer_),
        boost::asio::transfer_at_least(1),
        boost::bind(
            &HTTP::Session::received, 
            shared_from_this(), 
            boost::asio::placeholders::error, 
            boost::asio::placeholders::bytes_transferred
        )
    );
}