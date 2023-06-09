/*
    TimeStamp类是一个用于记录时间戳的类。
    它主要用于网络库中事件的时间戳，如事件的创建时间、到达时间等。

    这个类封装了一个64位的整数，用来表示从1970年1月1日零时零分零秒（UTC协调世界时）到当前时间的毫秒数。
    同时，该类还实现了一些常用的时间处理函数，比如将时间戳转换成字符串形式等。

    基于此，muduo网络库可以通过TimeStamp记录事件的发生时间以及事件在队列中等待的时间，
    从而更好地控制事件的发生和处理。
*/
#ifndef MUDUO_BASE_TIMESTAMP
#define MUDUO_BASE_TIMESTAMP

// #include "muduo/base/copyable.h"
// #include "muduo/base/Types.h"


#include "copyable.h"
#include "Types.h"

#include <boost/operators.hpp>

namespace muduo {
    class TimeStamp : public muduo::copyable,
                      public boost::equality_comparable<TimeStamp>,   // 支持相等比较
                      public boost::less_than_comparable<TimeStamp>   // 支持小于比较
    {
        public:
        // 构造一个无效的时间戳，即将 microSecondsSinceEpoch_ 设为 0
        TimeStamp() :microSecondsSinceEpoch_(0) {}

        explicit TimeStamp(int64_t microSecondsSinceEpochArg) : microSecondsSinceEpoch_(microSecondsSinceEpochArg){}

        // 交换两个时间戳对象的值，用于实现移动语义。
        void swap(TimeStamp& that) {
            std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
        }

        // 将时间戳转换成字符串形式
        string toString() const;
        //  toFormattedString 还包括了可选的是否显示微秒
        string toFormattedString(bool showMicroseconds = true) const;
        
        // 判断该时间戳是否有效，即 microSecondsSinceEpoch_ 是否大于 0。
        bool valid() const {
            return microSecondsSinceEpoch_ > 0;
        }

        // 返回以微秒为单位的时间戳。
        int64_t microSecondsSinceEpoch() const {
            return microSecondsSinceEpoch_;
        }
        // 返回以秒为单位的时间戳。
        time_t secondsSinceEpoch() const {
            return static_cast<time_t>(microSecondsSinceEpoch_ / KMicroSencondsPerSecond);
        }


        // Get time of now. 返回当前时间戳。
        static TimeStamp now();
        
        // 返回一个无效的时间戳，即构造函数中将 microSecondsSinceEpoch_ 设为 0 的结果。
        static TimeStamp invalid() {
            return TimeStamp();
        }

        // 从 Unix 时间和微秒数构造时间戳
        // 这两个函数用于方便地将 Unix 时间转换为时间戳。
        static TimeStamp fromUnixTime(time_t t) {
            return fromUnixTime(t, 0);
        }

        // 从 Unix 时间和微秒数构造时间戳
        static TimeStamp fromUnixTime(time_t t, int microseconds) {
            // kMicroSecondsPerSecond 为 1000000，即一秒对应的微秒数。
            return TimeStamp(static_cast<int64_t>(t) * KMicroSencondsPerSecond + microseconds);
        }

        static const int KMicroSencondsPerSecond = 1000 * 1000;

        private:
        int64_t microSecondsSinceEpoch_;
    };

    inline bool operator<(TimeStamp lhs, TimeStamp rhs) {
        return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
    }

    inline bool operator==(TimeStamp lhs, TimeStamp rhs) {
        return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
    }

    // Gets time difference of two timestamps, result in seconds.
    inline double timeDifference(TimeStamp high, TimeStamp low)
    {
        int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
        return static_cast<double>(diff) / (1000 * 1000);
    }

    // Add @c seconds to given timestamp.
    // @return timestamp+seconds as Timestamp
    inline TimeStamp addTime(TimeStamp timestamp, double seconds)
    {
        int64_t delta = static_cast<int64_t>(seconds * 1000 * 1000);
        return TimeStamp(timestamp.microSecondsSinceEpoch() + delta);
    }
} // namespace muduo

#endif