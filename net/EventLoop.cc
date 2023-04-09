#include "../net/EventLoop.h"

using namespace muduo;
using namespace muduo::net;

namespace
{
    __thread EventLoop* t_loopInThisThread = 0;

    EventLoop::EventLoop() : looping_(false), threadId_(CurrentThread::tid()) {
        LOG_TRACE << "EventLoop created " << this << " in thread " << threadId_;
        if(t_loopInThisThread) {
            LOG_FATAL << "Another EventLoop " << t_loopInThisThread << " exists in this thread " << threadId_;

        }
    }


} // namespace