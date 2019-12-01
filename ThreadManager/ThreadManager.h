#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio/executor_work_guard.hpp>

namespace Thread{
    class ThreadManager{
        public:
            static Thread::ThreadManager& get_instance(){
                static Thread::ThreadManager single;
                return single;
            }

            ~ThreadManager(){
                thread_group_.join_all();
            }

            boost::shared_ptr<boost::asio::io_context>& get_io_context();

        private:
            unsigned int get_index();
            void create_thread(boost::shared_ptr<boost::asio::io_context>& ioc);

            ThreadManager()
            :   io_count_(4),
                index_(0)
            {
                for(int i = 0; i < io_count_; ++i) io_vector_.push_back(boost::make_shared<boost::asio::io_context>());

                std::cout<<std::this_thread::get_id()<<" : ThreadManager()\n";
                for(int i = 0; i < io_count_; ++i){
                    thread_group_.create_thread(boost::bind(&Thread::ThreadManager::create_thread, this, std::ref(io_vector_[i])));
                }
            }

            unsigned int index_;
            unsigned int io_count_;

            std::vector<boost::shared_ptr<boost::asio::io_context>> io_vector_;
            std::vector<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>> io_work_vector_;
            boost::thread_group thread_group_;

            boost::asio::io_context thread_manager_ioc_;
            std::mutex mutex_;
            std::mutex get_io_context_mutex_;

    };
};


