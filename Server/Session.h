#pragma once

#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace HTTP{
    class Session : public boost::enable_shared_from_this<HTTP::Session>{
        public:
            typedef std::vector<unsigned char> buffer_type;
            
            Session(boost::shared_ptr<boost::asio::io_context>& ioc) 
            :   socket_(*ioc),
                buffer_(buffer_type(1024 * 1024)),
                session_ioc_(ioc)
            {}
            
            Session(boost::asio::io_context& ioc)
            :   socket_(ioc),
                buffer_(buffer_type(1024 * 1024))
            {}
            
            boost::asio::ip::tcp::socket& get_socket();
            void receive();

        private:
            void written(boost::system::error_code const& ec, std::size_t transferred);
            void write();
            void received(boost::system::error_code const& ec, std::size_t transferred);

            boost::asio::ip::tcp::socket socket_;
            boost::shared_ptr<boost::asio::io_context> session_ioc_;
            
            buffer_type buffer_;

    };
};