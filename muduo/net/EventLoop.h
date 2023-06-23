#ifndef MUDUO_NET_EVENTLOOP_H
#define MUDUO_NET_EVENTLOOP_H

#include "../../project/muduo/muduo/base/noncopyable.h"
#include "../../project/muduo/muduo/base/CurrentThread.h"

#include "Callbacks.h"
#include "TimerQueue.h"

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
            typedef std::function<void()> Functor;
            EventLoop();
            ~EventLoop();

            void loop();
            void quit();

            TimeStamp pollReturnTime() const {return pollReturnTime_;}
            int64_t iteration()        const { return iteration_; }

            void runInLoop(Functor cb);

            void queueInLoop(Functor cb);

            size_t queueSize() const;

            // timers

            /// Runs callback at 'time'
            TimerId runAt(TimeStamp time, TimerCallback cb);

            ///
            TimerId runAfter(double delay, TimerCallback cb);

            /// 
            TimerId runEvery(double interval, TimerCallback);

            // cancles the timer
            void cannel(TimerId timerid);

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
            bool eventHandling() const { return eventHandling_; }

            void setContext(const boost::any& context)
            { context_ = context; }

            const boost::any& getContext() const
            { return context_; }

            boost::any* getMutableContext()
            { return &context_; }

            static EventLoop* getEventLoopOfCurrentThread();

            private:

            void abortNotLoopThread();

            void handleRead();

            void doPendingFunctors();

            typedef std::vector<Channel*> ChannelList;

            bool looping_;
            std::atomic<bool> quit_;
            bool eventHandling_;           /* atomic */
            bool callingPendingFunctors_;  /* atomic */
            int64_t iteration_;
            const pid_t threadId_;            // 本对象所属的线程
            TimeStamp pollReturnTime_;
            std::unique_ptr<Poller> poller_;
            std::unique_ptr<TimerQueue> timerQueue_;
            int wakeupFd_;
            
            /*
                用于处理weakupFd_上的readbable事件，将事件分发给handleRead（）函数
            */
            std::unique_ptr<Channel> wakeupChannel_;
            boost::any context_;
            
            // scratch variables
            ChannelList activeChannels_;
            Channel* currentActiveChannel_;

            /*
                暴露给了其他线程，所以使用mutex保护
            */
            mutable MutexLock mutex_;
            std::vector<Functor> pendingFunctors_ GUARDED_BY(mutex_);

        };
    }
}


#endif