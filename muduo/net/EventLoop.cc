#include "muduo/net/EventLoop.h"

#include "muduo/base/Logging.h"
#include "muduo/base/CurrentThread.h"

#include <unistd.h>
#include <assert.h>

using namespace muduo;
using namespace muduo::net;

namespace
{
    __thread EventLoop* t_loopInThisThread = 0;

    /* 
        返回 EventLoop 对象 
    */
    EventLoop* EventLoop::getEventLoopOfCurrentThread() {
        return t_loopInThisThread;
    }

    EventLoop::EventLoop() :looping_(false), 
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

    void EventLoop::loop() {
        assert(!looping_);
        assertInLoopThread();
        looping_ = true;

        ::poll(NULL, 0, 5*1000);

        LOG_TRACE << "EventLoop" << this << " stop looping";
        looping_ = false;
    }
} // namespace