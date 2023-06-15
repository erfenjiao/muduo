
// #include "muduo/base/Thread.h"
// #include "muduo/base/CurrentThread.h"
#include "Thread.h"
#include "CurrentThread.h"
#include "Logging.h"

#include <type_traits>

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>




namespace muduo
{
    namespace detail
    {
        pid_t getpid(){
            return static_cast<pid_t>(::syscall(SYS_getpid));
        }


        /*
            ThreadData类用于保存新线程创建时将传递给它的数据
        */
       struct ThreadData {
        typedef muduo::Thread::ThreadFunc ThreadFunc;
        ThreadFunc func_;
        string name_;
        pid_t* tid_;
        CountLatch* latch_;

        ThreadData(ThreadFunc func, string name, pid_t* tid, CountLatch* latch)
                :func_(func),
                 name_(name),
                 tid_(tid),
                 latch_(latch)
                 {}
        
        void runInThread() {
            LOG_INFO << "runInTread()" ;


       }

       };

       

        /*
            新线程的入口点，它运行ThreadData对象的runInThread()方法。
        */
        void* startThread(void* obj) {
            ThreadData* data = static_cast<ThreadData*>(obj);
            data->runInThread();
            delete data;
            return NULL;
        }


        
    } // namespace detail

    

    Thread::Thread(ThreadFunc func, const string& n)
       : started_(false),
         joined_(false),
         tid_(0),
         pthreadId_(0),
         func_(std::move(func)),
         latch_(1)
    {
        setDefaultName();
    }

    Thread::~Thread() {
        if(started_ && joined_) {
            pthread_detach(pthreadId_);
        }
    }

    void Thread::setDefaultName(){
        int num = numCreated_.incrementAndGet();
        if (name_.empty())
        {
            char buf[32];
            snprintf(buf, sizeof buf, "Thread%d", num);
            name_ = buf;
        }
    }

    /*
        首先创建一个新的线程，然后将状态started_设为true，表示线程已经开始运行
    */
    void Thread::start() {
        assert(!started_);
        started_ = true;
        detail::ThreadData* data = new detail::ThreadData(func_, name_, &tid_, &latch_);
        if(pthread_create(&pthreadId_, NULL, &detail::startThread, data)) {
            started_ = false;
            delete data;
            LOG_SYSFATAL << "Failed in pthread_create";
        } else {
            latch_.wait();
            assert(tid_ > 0);
        }
    }


    void CurrentThread::cacheTid() {
            if(t_cachedTid == 0) {
                t_cachedTid = detail::getpid();
                t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, " %5d", t_cachedTid);
            }
    }

    bool CurrentThread::isMainThread() {
        return tid() == ::getpid();
    }
    
} // namespace muduo
