#include "ThreadManager.h"

boost::shared_ptr<boost::asio::io_context>& Thread::ThreadManager::get_io_context(){
    std::lock_guard<std::mutex> g(get_io_context_mutex_);

    if(io_vector_[index_].get() == nullptr)
    {
        std::cout<<index_<<" : io_context nullptr\n";
        io_vector_[index_] = boost::make_shared<boost::asio::io_context>();
        thread_group_.create_thread(boost::bind(&Thread::ThreadManager::create_thread, this, std::ref(io_vector_[index_])));
        return io_vector_[index_];
    }

    return io_vector_[get_index()];    
}

unsigned int Thread::ThreadManager::get_index(){
    if((index_ > io_count_ - 1 == false) || (index_ + 1 > io_count_ - 1)){
            index_ = 0;
            return index_;
    }

    return ++index_;    
}

void Thread::ThreadManager::create_thread(boost::shared_ptr<boost::asio::io_context>& ioc){
    mutex_.lock();

    std::cout<<std::this_thread::get_id()<<" : "<<"ThreadManager thread_group create thread\n";

    boost::system::error_code ec;

    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> w(ioc->get_executor());

    mutex_.unlock();
    ioc->run(ec);

    if(ec) std::cerr<<ec.message()<<"\n";

    std::cout<<std::this_thread::get_id()<<" : "<<"ThreadManager thread end\n";
}