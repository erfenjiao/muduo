#ifndef MUDUO_BASE_COUNTDOWNLATCH_H
#define MUDUO_BASE_COUNTDOWNLATCH_H

#include "muduo/base/Condition.h"
#include "muduo/base/Mutex.h"

namespace muduo {
    class CountLatch : noncopyable {
        public:


        private:
        mutable MutexLock mutex_;
        Condition condition_ GUARDED_BY(mutex_);
        int count_ GUARDED_BY(mutex_);
    }
}

#endif