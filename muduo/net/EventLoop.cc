// #include "muduo/net/EventLoop.h"
// #include "muduo/net/Channel.h"
// #include "muduo/net/Poller.h"

// #include "muduo/base/Logging.h"
// #include "muduo/base/CurrentThread.h"

#include "EventLoop.h"
#include "Channel.h"
#include "Poller.h"

#include "../base/Logging.h"
#include "../base/CurrentThread.h"

#include <unistd.h>
#include <assert.h>


using namespace muduo;
using namespace muduo::net;

namespace
{
    __thread EventLoop* t_loopInThisThread = 0;

    const int kPollTimeMs = 10000;

    // int createEventfd()
    // {
    // int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    // if (evtfd < 0)
    // {
    //     LOG_SYSERR << "Failed in eventfd";
    //     abort();
    // }
    // return evtfd;
    // }

    // #pragma GCC diagnostic ignored "-Wold-style-cast"
    // class IgnoreSigPipe
    // {
    // public:
    // IgnoreSigPipe()
    // {
    //     ::signal(SIGPIPE, SIG_IGN);
    //     // LOG_TRACE << "Ignore SIGPIPE";
    // }
    // };
    // #pragma GCC diagnostic error "-Wold-style-cast"

    // IgnoreSigPipe initObj;
}  // namespace

/* 
    返回 EventLoop 对象 
*/
EventLoop* EventLoop::getEventLoopOfCurrentThread(){
    return t_loopInThisThread;
}

/*
    构造函数
*/
EventLoop::EventLoop():looping_(false), 
                        threadId_(CurrentThread::tid()) {
    LOG_TRACE << "EventLoop created " << this << " in thread " << threadId_;

    if(t_loopInThisThread) {
        LOG_FATAL << "Another EventLoop " << t_loopInThisThread << " exists in this thread " << threadId_;
    }
    else {
        t_loopInThisThread = this;
    }
}

EventLoop::~EventLoop() {
    assert(!looping_);
    t_loopInThisThread = NULL;
}

// 事件循环
void EventLoop::loop() {
    assert(!looping_);
    assertInLoopThread();
    looping_ = true;

    //poll(NULL, 0, 5*1000);

    LOG_TRACE << "EventLoop" << this << " stop looping";
    looping_ = false;
}

void EventLoop::abortNotLoopThread() {
    LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop" << this
                << "was created in threadId_ = " << threadId_
                << ", current thread id = " << CurrentThread::tid(); 
}

void EventLoop::updateChannel(Channel* channel) {
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    poller_->updateChannel(channel);
}