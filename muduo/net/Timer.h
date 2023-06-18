#ifndef MUDUO_NET_TIMER_H
#define MUDUO_NET_TIMER_H

#include "../base/Atomic.h"
#include "../base/TimeStamp.h"
#include "Callbacks.h"

/*
    定义定时器事件，并提供了相关的方法和数据成员来管理和操作定时器事件。
    支持设置回调函数、过期时间、重复间隔等操作。

    它的代码实现包括：
        1. 在构造函数中初始化成员变量，包括定时器回调函数、过期时间、重复间隔等。
        2. run()函数，表示定时器触发时要执行的回调函数。
        3. restart()函数，用于重新启动定时器，更新过期时间等。
        4. numCreated()函数，用于获取已创建定时器的数量。
*/

namespace muduo
{
    namespace net
    {
        class Timer : noncopyable {
            public:
            Timer(TimerCallback cb, TimeStamp when, double interval) 
            : callback_(std::move(cb)),
              expiration_(when),
              interval_(interval),
              repeat_(interval > 0.0),
              sequence_(s_numCreated_.incrementAndGet())
            {
            }

            void run() const
            {
                callback_();
            }

            TimeStamp expiration() const  { return expiration_; }
            bool repeat() const { return repeat_; }
            int64_t sequence() const { return sequence_; }

            void restart(TimeStamp now);

            static int64_t numCreated() { return s_numCreated_.get(); }



            private:
            const TimerCallback callback_;  // 定时器回调，即定时器到期时需要执行的回调函数
            TimeStamp expiration_;          // 定时器的到期时间戳
            const double interval_;         // 定时器的间隔时间，如果是一次性定时器则该值为0
            const bool repeat_;             // 定时器是否重复触发
            const int64_t sequence_;        // 定时器序号，用于标记定时器

            static AtomicInt64 s_numCreated_;  // 静态成员变量，它记录了该定时器类已经创建的定时器数量。



        };

    } // namespace net
    
} // namespace muduo

#endif