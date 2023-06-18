#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif

#include "TimerQueue.h"

#include "../base/Logging.h"
#include "EventLoop.h"
#include "Timer.h"
#include "TimerId.h"

#include <sys/timerfd.h>
#include <unistd.h>

namespace muduo
{
    namespace net
    {
        namespace detail
        {
            int createTimerfd() {
                /*
                    用错函数了
                    Create new per-process timer using CLOCK_ID.  
                    extern int timer_create (clockid_t __clock_id,
                                            struct sigevent *__restrict __evp,
                                            timer_t *__restrict __timerid) __THROW;

                    Return file descriptor for new interval timer source. 
                    用于创建定时器文件描述符 
                    extern int timerfd_create (__clockid_t __clock_id, int __flags) __THROW;
                    __clock_id 表示使用哪个时钟来实现定时器
                    __flags    是一个位掩码，用于指定定时器的行为

                    可以使用该描述符进行计时器操作，例如设置、启动和停止定时器
                */
                int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
                if(timerfd < 0) {
                    LOG_SYSFATAL << "Failed in timerfd_create";
                }
                return timerfd;
            }
        } // namespace detail
        
    } // namespace net
    
} // namespace muduo

using namespace muduo;
using namespace muduo::net;
using namespace muduo::net::detail;

TimerQueue::TimerQueue(EventLoop* loop) : loop_(loop),
timerfd_(createTimerfd()),
timerfdChannel_(loop, timerfd_),
timers_(),
callingExpiredTimers_(false)
{

}