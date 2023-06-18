
#include "Timer.h"

using namespace muduo;
using namespace net;

AtomicInt64 Timer::s_numCreated_;

/*
    restart() 函数，作用是重新启动计时器。它接受一个时间戳（now）参数，表示从哪个时间点开始重新计时。
    
    如果计时器是可重复的（repeat_ == true），则会将过期时间（expiration_）设置为当前时间加上时间间隔（interval_）；
    
    否则，过期时间会被设置为无效时间戳（Timestamp::invalid()）。
*/
void Timer::restart(TimeStamp now) {
    if(repeat_){
        expiration_ = addTime(now, interval_);
    } 
    else{
        expiration_ = TimeStamp::invalid();
    }
}