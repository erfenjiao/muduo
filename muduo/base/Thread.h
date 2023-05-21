#ifndef MUDUO_BASE_THREAD_H
#define MUDUO_BASE_THREAD_H

// #include "muduo/base/Atomic.h"
// #include "muduo/base/CountDownLatch.h"
// #include "muduo/base/Types.h"


#include "Atomic.h"
#include "CountDownLatch.h"
#include "Types.h"

#include <functional>
#include <memory>
#include <pthread.h>

namespace muduo
{
    class Thread : noncopyable{
        public:
        //回调
        typedef std::function<void()> ThreadFunc();

        // C++中的一个类构造函数，用于创建一个新的线程对象。
        // ThreadFunc：线程执行的入口函数，可以是全局函数、静态成员函数或者是lambda表达式。
        // name：线程的名称，可选参数，缺省值为一个空字符串。
        explicit Thread(ThreadFunc, const string& name = string());
        ~Thread();

        void start();
        void join();


        pid_t tid() const {
            return tid_;
        }

        private:
        pid_t tid_;

    };
} // namespace muduo



#endif