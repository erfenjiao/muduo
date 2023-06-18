
#ifndef MUDUO_NET_TIMERID
#define MUDUO_NET_TIMERID

#include "../base/copyable.h"

#include <cstdint>
#include <cstddef>

/*
    表示定时器的ID
    每个定时器都对应着一个唯一的ID，该ID由定时器队列分配。
    其中，timer_成员变量指向该定时器对象，sequence_成员变量则是序列号，用于标识该定时器在定时器队列中的位置。

    通过TimerId类，可以方便地管理和操作定时器。
    例如，在定时器队列中添加、删除定时器时，需要先获取该定时器的TimerId，然后再执行相应的操作。
*/

namespace muduo
{
    namespace net
    {
        class Timer;

        class TimerId : public muduo::copyable {
            public:

            TimerId() : timer_(NULL),
                        sequence_(0)
            {
            }

            TimerId(Timer* timer, int64_t seq)
                : timer_(timer),
                sequence_(seq)
            {
            }

            // default copy-ctor, dtor and assignment are okay

            friend class TimerQueue;


            private:
            Timer* timer_;
            int64_t sequence_;
        };
    } // namespace net
    
} // namespace muduo


#endif