#pragma once

#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

namespace HTTP{
    class Session{
        public:
            typedef std::vector<unsigned char> buffer_type;
            
            Session(boost::shared_ptr<boost::asio::io_context>& ioc) 
            :   socket_(*ioc),
                buffer_(buffer_type(1024 * 1024)),
                session_ioc_(ioc)
            {}
            
            Session(boost::asio::io_context& ioc)
            :   socket_(ioc),
                buffer_(buffer_type(1024 * 1024))//,
               // session_ioc_(boost::make_shared<boost::asio::io_context>(ioc))
            {}
            
            boost::asio::ip::tcp::socket& get_socket();

            void receive();

        private:
            void received();

            boost::asio::ip::tcp::socket socket_;
            boost::shared_ptr<boost::asio::io_context> session_ioc_;
            
            buffer_type buffer_;

    };
};