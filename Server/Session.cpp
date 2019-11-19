#include "Session.h"

boost::asio::ip::tcp::socket& HTTP::Session::get_socket(){
    return socket_;
}

// HTTP::Session::buffer_type& get_buffer(){
//     return buffer_;
// }

// boost::asio::io_context& get_io_context(){
//     return session_ioc_;
// }

void HTTP::Session::received(){
    std::cout<<__PRETTY_FUNCTION__<<"\n";
}

void HTTP::Session::receive(){
    std::cout<<__PRETTY_FUNCTION__<<"\n";

    boost::asio::async_read(
        socket_,
        boost::asio::buffer(buffer_),
        boost::asio::transfer_at_least(1),
        [&](boost::system::error_code const& ec, std::size_t transferred){
            buffer_.resize(transferred);
            std::cout<<"Received : "<<buffer_.data()<<"\n";

            receive();
        }
    );
}