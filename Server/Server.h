#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>

#include "Session.h"

namespace HTTP{
    class Server{
        public:
            
            Server(boost::shared_ptr<boost::asio::io_context>& ioc, boost::asio::ip::tcp::endpoint ep)
                : acceptor_(*ioc, ep)
                , server_endpoint_(ep.protocol(), ep.port())
            {
            }

            void start();
            void stop();
            
        private:
            void accepted();
            void accept();

            boost::asio::ip::tcp::endpoint server_endpoint_;
            boost::asio::ip::tcp::acceptor acceptor_;
            boost::shared_ptr<HTTP::Session> session_;
    };
};