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
            
            Server(boost::asio::io_context& ioc, boost::asio::ip::tcp::endpoint ep)
                : acceptor_(ioc, ep)
                , session_ioc_(5)
                , session_index_(0)
                , server_endpoint_(ep.protocol(), ep.port())
            {
            }

            void start();
            void stop();
            
        private:
            void accepted();
            void accept();

            boost::thread_group tg_;

            boost::asio::ip::tcp::endpoint server_endpoint_;

            std::vector<boost::asio::io_context> session_ioc_;
            unsigned int session_index_;
            unsigned int get_session_index();

            boost::asio::ip::tcp::acceptor acceptor_;

            boost::shared_ptr<HTTP::Session> session_;
    };
};