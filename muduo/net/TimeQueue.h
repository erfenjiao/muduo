#ifndef MUDUO_NET_TIMERQUEUE_H
#define MUDUO_NET_TIMERQUEUE_H

#include <set>
#include <vector>

#include "../base/Mutex.h"
#include "../base/TimeStamp.h"
#include "Callbacks.h"
#include "Channel.h"

namespace muduo
{
    namespace net
    {
        class EventLoop;
        class Timer;
        class TimerId;

        class TimeQueue : noncopyable{
            public:
            explicit TimeQueue(EventLoop* loop);
            ~TimeQueue();

             ///
            /// Schedules the callback to be run at given time,
            /// repeats if @c interval > 0.0.
            ///
            /// Must be thread safe. Usually be called from other threads.
            TimerId addTimer(TimerCallback cb, TimeStamp when, double interval);

            void cancel(TimerId timerId);

            private:

             // FIXME: use unique_ptr<Timer> instead of raw pointers.
            // This requires heterogeneous comparison lookup (N3465) from C++14
            // so that we can find an T* in a set<unique_ptr<T>>.
            typedef std::pair<TimeStamp, Timer*> Entry;
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
            Channel timerfdChannel_;
            // Timer list sorted by expiration
            TimerList timers_;

            // for cancel()
            ActiveTimerSet activeTimers_;
            bool callingExpiredTimers_; /* atomic */
            ActiveTimerSet cancelingTimers_;

        };
    } // namespace net
    
} // namespace muduo


#endif