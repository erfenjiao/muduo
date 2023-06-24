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
#include <vector>

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

            struct timespec howMuchTimeFromNow(TimeStamp when){
                int64_t microseconds = when.microSecondsSinceEpoch() - TimeStamp::now().microSecondsSinceEpoch();
                if(microseconds < 100){
                    microseconds = 100;
                }
                struct timespec ts;
                ts.tv_sec = static_cast<time_t>(microseconds/TimeStamp::KMicroSencondsPerSecond);
                ts.tv_nsec = static_cast<long>(
                    (microseconds % TimeStamp::KMicroSencondsPerSecond) * 1000);
                return ts;
            }

            void resetTimerfd(int timerfd, TimeStamp expiration){
                struct itimerspec newValue;
                struct itimerspec oldValue;
                memZero(&newValue, sizeof newValue);
                memZero(&oldValue, sizeof oldValue);
                newValue.it_value = howMuchTimeFromNow(expiration);
                int ret = ::timerfd_settime(timerfd, 0, &newValue, &oldValue);
                if(ret){
                    LOG_SYSERR << "timerfd_settime()";
                }
            }
        } // namespace detail
        
    } // namespace net
    
} // namespace muduo

using namespace muduo;
using namespace muduo::net;
using namespace muduo::net::detail;

TimerQueue::TimerQueue(EventLoop* loop) 
                    : loop_(loop),
                    timerfd_(createTimerfd()),
                    timerfdChannel_(loop, timerfd_),
                    timers_(),                    // TimerList timers_;
                    callingExpiredTimers_(false)
{
    /*
        muduo::net::Channel muduo::net::TimerQueue::timerfdChannel_
        void setReadCallback(ReadEventCallback cb)
            { readCallback_ = std::move(cb); }
    */
    timerfdChannel_.setReadCallback(std::bind(&TimerQueue::handleRead, this));
    timerfdChannel_.enableReading();
}

TimerQueue::~TimerQueue() {
    timerfdChannel_.disableAll();
    timerfdChannel_.remove();
    ::close(timerfd_);
    for(const Entry& timer : timers_) {
        delete timer.second;
    }
}

TimerId TimerQueue::addTimer(TimerCallback cb, TimeStamp when, double interval) {
    LOG_INFO << "cb = ", cb;
    Timer* timer = new Timer(std::move(cb), when, interval);
    loop_->runInLoop(std::bind(&TimerQueue::addTimerInLoop, this, timer));
    return TimerId(timer, timer->sequence());
}

void TimerQueue::cancel(TimerId timerId) {
    loop_->runInLoop(std::bind(&TimerQueue::cancelInLoop, this, timerId));
}

void TimerQueue::cancelInLoop(TimerId timerId){
    loop_->assertInLoopThread();
    assert(timers_.size() == activeTimers_.size());
    ActiveTimer timer(timerId.timer_, timerId.sequence_);
    ActiveTimerSet::iterator it = activeTimers_.find(timer);
    if(it != activeTimers_.end()) {
        size_t n = timers_.erase(Entry(it->first->expiration(), it->first));
        assert(n == 1);
        (void)n;
        delete it->first;
        activeTimers_.erase(it);
    }
    else if (callingExpiredTimers_)
    {
        cancelingTimers_.insert(timer);
    }
    assert(timers_.size() == activeTimers_.size());
}
/*
    修改定时器列表
*/
void TimerQueue::addTimerInLoop(Timer* timer){
    loop_->assertInLoopThread();
    bool earliestChanged = insert(timer);

    if(earliestChanged) {
        resetTimerfd(timerfd_, timer->expiration());
    }
}

bool TimerQueue::insert(Timer* timer) {
    loop_->assertInLoopThread();
    assert(timers_.size() == activeTimers_.size());
    bool earliestChanged = false;

    //TimeStamp expiration() const  { return expiration_; }
    TimeStamp when = timer->expiration();
    TimerList::iterator it = timers_.begin();
    if(it == timers_.end() || when < it->first){
        earliestChanged = true;
    }

}


std::vector<TimerQueue::Entry> TimerQueue::getExpired(TimeStamp now) {
    std::vector<Entry> expired;
    /*
        std::make_pair() 是一个函数模板，用于将两个值构造成一个 std::pair 对象。
        第一个参数是 now，第二个参数是指针类型 Timer* 的最大值转换而来的无符号整数类型 uintptr_t 的指针。

        reinterpret_cast 运算符用于进行类型转换。
        它可以将一种指针类型转换为另一种指针类型，甚至可以将指针类型转换为整数类型或者整数类型转换为指针类型。
        在这里， reinterpret_cast<Timer*>(UINTPTR_MAX) 将无符号整数类型的最大值强制转换为指向 Timer 类型的指针。
        这样做的目的可能是为了提供一个无效的指针作为占位符，以便稍后替换为有效的指针。

        因此，sentry 会被赋值为一个 std::pair 对象，其中第一个元素是当前时间戳 now，第二个元素是一个无效的指向 Timer 类型对象的指针。
    */
    Entry sentry = std::make_pair(now, reinterpret_cast<Timer*>(UINTPTR_MAX));
    //typedef std::set<Entry> TimerList;
    // lower_bound函数将返回一个迭代器，该迭代器指向第一个未到期的定时器。
    TimerList::iterator it = timers_.lower_bound(sentry);
    assert(it == timers_.end() || now < it->first);
    std::copy(timers_.begin(), it, back_inserter(expired));
    timers_.erase(timers_.begin(), it);

    return expired;
}

