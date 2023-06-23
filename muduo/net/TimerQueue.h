#ifndef MUDUO_NET_TIMERQUEUE_H
#define MUDUO_NET_TIMERQUEUE_H

#include <set>
#include <vector>

#include "../base/Mutex.h"
#include "../base/TimeStamp.h"
#include "Callbacks.h"
#include "Channel.h"

/*
    根据当前时间，高效的寻找已经到期的Timer，也要高效的添加和删除Timer
*/

namespace muduo
{
    namespace net
    {
        class EventLoop;
        class Timer;
        class TimerId;

        class TimerQueue : noncopyable{
            public:
            explicit TimerQueue(EventLoop* loop);
            ~TimerQueue();

             ///
            /// Schedules the callback to be run at given time,
            /// repeats if @c interval > 0.0.
            ///
            /// Must be thread safe. Usually be called from other threads.
            TimerId addTimer(TimerCallback cb, TimeStamp when, double interval);

            void cancel(TimerId timerId);

            private:

       
            typedef std::pair<TimeStamp, Timer*> Entry;
            // set 因为只有key没有alue
            typedef std::set<Entry> TimerList;
            typedef std::pair<Timer*, int64_t> ActiveTimer;
            typedef std::set<ActiveTimer> ActiveTimerSet;

            void addTimerInLoop(Timer* timer);
            void cancelInLoop(TimerId timerId);
            // called when timerfd alarms
            void handleRead();

            // move out all expired timers，并通过ector返回
            std::vector<Entry> getExpired(TimeStamp now);
            void reset(const std::vector<Entry>& expired, TimeStamp now);

            bool insert(Timer* timer);

            EventLoop* loop_;
            const int timerfd_;
            // 观察 Timer 上的 readable 事件
            Channel timerfdChannel_;
            // Timer list sorted by expiration
            TimerList timers_;

            // for cancel()
            ActiveTimerSet activeTimers_;
            bool callingExpiredTimers_;       /* atomic */
            ActiveTimerSet cancelingTimers_;

        };
    } // namespace net
    
} // namespace muduo


#endif