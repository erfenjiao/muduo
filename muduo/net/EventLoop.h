#ifndef MUDUO_NET_EVENTLOOP_H
#define MUDUO_NET_EVENTLOOP_H

#include "muduo/base/noncopyable.h"
#include "muduo/base/CurrentThread.h"

namespace muduo{
    namespace net{
        class EventLoop : noncopyable {
            public:
            EventLoop();
            ~EventLoop();

            void loop();
            void quit();

            /*
                assertInLoopThread()函数会断言当前线程是否为指定的IO线程，如果不是，则会触发断言失败
            */
            void assertInLoopThread() {
                if(!isInLoopThread()) {
                    abortNotLoopThread();
                }
            }

            bool isInLoopThread() const {
                return threadId_ == CurrentThread::tid();
            }

            static EventLoop* getEventLoopOfCurrentThread();

            private:

            void abortNotLoopThread();

            bool looping_;
            const pid_t threadId_; // 本对象所属的线程

        };
    }
}


#endif