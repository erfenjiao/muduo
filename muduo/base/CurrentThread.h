#ifndef MUDUO_BASE_CURRENTTHREAD_H
#define MUDUO_BASE_CURRENTTHREAD_H
/**
 * 用于获取当前线程ID和线程名称的文件
*/
#include "muduo/base/Types.h"

namespace muduo {
    namespace CurrentThread {
        /*
        *   __thread修饰的变量是线程局部存储的。
            线程真实pid（tid）的缓存，是为了减少::syscall(SYS_gettid)系统调用的次数
            提高获取tid的效率
        */
        extern __thread int  t_cachedTid;
        extern __thread char t_tidString[32];
        extern __thread int t_tidStringLength;
        extern __thread const char* t_threadName;

        void cacheTid();

        inline int tid() {
            // __builtin_expect: 
            // gcc引入的，作用是允许程序员将最有可能执行的分支告诉编译器
            // 写法为：__builtin_expect(EXP, N)
            // 意思是: EXP==N的概率很大
            if(__builtin_except(t_cachedTid == 0, 0)) {
                cacheTid();
            }
            return t_cachedTid;
        }

        inline const char* tidString() {
            return t_tidString;
        }

        inline int tidStringLength() // for logging
        {
            return t_tidStringLength;
        }

        inline const char* name()
        {
            return t_threadName;
        }

        bool isMainThread();   // 是否是主线程

        void sleepUsec(bool demangle);
    }
}

#endif
