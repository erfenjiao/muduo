#include "EventLoopThread.h"
#include "EventLoop.h"

using namespace muduo;
using namespace muduo::net;

EventLoopThread::EventLoopThread(const ThreadInitCallback& cb, 
                                 const string& name )
                            : loop_(NULL),
                            existing_(false),
                            thread_(std::bind(&EventLoopThread::threadfunc, this), name),
                            mutex_(),
                            cond_(mutex_),
                            callback_(cb)
                                {}

EventLoopThread::~EventLoopThread(){
    existing_ = true;
    if(loop_ != NULL) {
        loop_->quit();
        thread_.join();
    }
}

/*
    启动自己的线程，并在其中运行EventLoop::loop()
*/
EventLoop* EventLoopThread::startLoop(){
    assert(!thread_.started());
    thread_.start();

    EventLoop* loop = NULL;
    {
        MutexLockGuard lock(mutex_);
        while(loop_ == NULL){
            // 用条件变量等待线程的创建和运行
            cond_.wait();
        }
        loop = loop_;
    }
    return loop;
}

/*

*/
void EventLoopThread::threadfunc(){
    EventLoop loop;
    {
        MutexLockGuard lock(mutex_);
        loop_ = &loop;
        cond_.notify();
    }

    loop.loop();
    //assert(exiting_);
    MutexLockGuard lock(mutex_);
    loop_ = NULL;
}