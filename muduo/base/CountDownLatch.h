#ifndef MUDUO_BASE_COUNTDOWNLATCH_H
#define MUDUO_BASE_COUNTDOWNLATCH_H

// #include "muduo/base/Condition.h"
// #include "muduo/base/Mutex.h"

#include "Condition.h"
#include "Mutex.h"

/*
    一个计数器，用于实现线程同步。
    该类提供了一个倒数计数器，当计数器的值变为0时，所有等待该计数器的线程将被唤醒

    在具体应用中，CountDownLatch通常用于等待一组任务完成后再继续执行下一步操作。
    例如，在一个服务启动过程中，可能需要先启动一些必要的服务，只有这些服务都启动成功后才能继续启动其他服务。
    这时可以使用CountDownLatch来实现等待必要服务全部启动完毕，然后再继续启动其他服务的逻辑。

    通过使用CountDownLatch类，我们可以避免手动编写复杂的线程同步代码，从而简化开发难度和降低错误率
*/

namespace muduo {
    class CountDownLatch : noncopyable {
        public:
        explicit CountDownLatch(int count);

        /* 
            等待计数器的值变为 0 ，如果当前计数器不为0，则会阻塞当前线程。
        */
        void wait();

        /*
            将计数器减少1。
        */
        void countDown();

        /*
            获取当前计数器的值。
        */
        int getCount() const;

        private:
        mutable MutexLock mutex_;                 // 互斥锁，用于保护计数器和条件变量的访问。
        Condition condition_ GUARDED_BY(mutex_);  // 条件变量，用于等待计数器的值变为0。
        int count_ GUARDED_BY(mutex_);            // 计数器的值。由于这个变量被多个线程同时访问，因此需要使用互斥锁进行保护。
    };
}

#endif