#ifndef MUDUO_NET_EVENTLOOP_H
#define MUDUO_NET_EVENTLOOP_H

#include "../base/noncopyable.h"
#include "../base/CurrentThread.h"

namespace muduo{
    namespace net{
        class EventLoop : noncopyable {
            public:
            EventLoop();
            ~EventLoop();

            void loop();
            void quit();

            void assertInLoopThread() {
                if(!isInLoopThread()) {
                    abortNotLoopThread();
                }
            }

            bool isInLoopThread() const {
                return threadId_ == CurrentThread::tid();
            }

            private:

            void abortNotLoopThread();

            bool looping_;
            const pid_t threadId_; // 本对象所属的线程

        };
    }
}


#endif