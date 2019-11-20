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
            
            Session(boost::asio::io_context& ioc) 
                : socket_(ioc), buffer_(buffer_type(1024 * 1024))
            {}
            
            boost::asio::ip::tcp::socket& get_socket();

            void receive();

        private:
            void received();

            boost::asio::io_context session_ioc_;
            boost::asio::ip::tcp::socket socket_;
            buffer_type buffer_;

    };
};