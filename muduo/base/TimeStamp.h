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

#include "muduo/base/copyable.h"
#include "muduo/base/Types.h"

#include <boost/operators.hpp>

namespace muduo {
    class TimeStamp : public muduo::copyable,
                      public boost::equality_comparable<TimeStamp>,
                      public boost::less_than_comparable<TimeStamp>
    {
        public:
        TimeStamp() :microSecondsSinceEpoch_(0) {}

        explicit TimeStamp(int64_t microSecondsSinceEpochArg) : microSecondsSinceEpoch_(microSecondsSinceEpochArg){}

        void swap(TimeStamp& that) {
            std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
        }

        string toString() const;
        string toFormattedString(bool showMicroseconds = true) const;
        
        bool valid() const {
            return microSecondsSinceEpoch_ > 0;
        }

        int64_t microSecondsSinceEpoch() const {
            return microSecondsSinceEpoch_;
        }
        time_t secondsSinceEpoch() const {
            return static_cast<time_t>(microSecondsSinceEpoch_ / KMicroSencondsPerSecond);
        }


        // Get time of now.
        static TimeStamp now();
        static TimeStamp invalid() {
            return TimeStamp();
        }

        static TimeStamp fromUnixTime(time_t t) {
            return fromUnixTime(t, 0);
        }

        static TimeStamp fromUnixTime(time_t t, int microseconds) {
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
        return static_cast<double>(diff) / TimeStamp::kMicroSecondsPerSecond;
    }

    // Add @c seconds to given timestamp.
    // @return timestamp+seconds as Timestamp
    inline TimeStamp addTime(TimeStamp timestamp, double seconds)
    {
        int64_t delta = static_cast<int64_t>(seconds * TimeStamp::kMicroSecondsPerSecond);
        return TimeStamp(timestamp.microSecondsSinceEpoch() + delta);
    }
} // namespace muduo

#endif