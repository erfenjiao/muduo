#ifndef MUDUO_NET_EVENTLOOP_H
#define MUDUO_NET_EVENTLOOP_H

#include "../../project/muduo/muduo/base/noncopyable.h"
#include "../../project/muduo/muduo/base/CurrentThread.h"

#include <atomic>
#include <functional>
#include <vector>

#include <boost/any.hpp>
#include <memory>

using namespace std;
/**
 * 事件分发器
*/

namespace muduo{
    namespace net{
        class Channel;
        class Poller;
        // TODO
        // class TimerQueue
        
        class EventLoop : noncopyable {
            public:
            EventLoop();
            ~EventLoop();

            void loop();
            void quit();

            // internal usage
            void wakeup();
            void updateChannel(Channel* channel);
            void removeChannel(Channel* channel);
            bool hasChannel(Channel* channel);

            /*
                每个线程只能有一个EventLoop对象，因此 EventLoop 构造函数需要检查当前线程是否已经创建了其他EventLoop对象
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

            typedef std::vector<Channel*> ChannelList;

            bool looping_;
            std::atomic<bool> quit_;
            const pid_t threadId_;            // 本对象所属的线程
            std::unique_ptr<Poller> poller_;

            // scratch variables
            ChannelList activeChannels_;

        };
    }
}


#endif