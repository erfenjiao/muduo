/**
 * Condition类是基于POSIX条件变量封装的一个类，它的主要功能是实现线程之间的同步和通信。具体来说，它提供了如下几个功能：

    等待条件变量：当一个线程在等待某个条件成立时，可以调用Condition::wait()函数使自己进入睡眠状态，等待其他线程通知条件变量。
    在睡眠状态下，该线程会自动释放其持有的互斥锁，以便其他线程可以访问共享资源。

    通知条件变量：当一个线程修改了共享资源，并且该资源可能满足其他线程等待的条件时，
    可以调用Condition::notify()或Condition::notifyAll()函数来通知其他线程。
    这些函数会唤醒正在等待条件变量的线程，并要求它们重新获取互斥锁。

    超时等待：Condition类还提供了一些支持超时等待的函数，
    如Condition::waitForSeconds()和Condition::waitForMilliSeconds()，
    可以让线程在等待条件变量时指定一个最长等待时间，避免无限等待导致的死锁问题。
*/

#ifndef MUDUO_BASE_CONDITION_H
#define MUDUO_BASE_CONDITION_H

// #include "muduo/base/Mutex.h"
#include "Mutex.h"

#include <pthread.h>

namespace muduo
{

class Condition : noncopyable
{
 public:
  explicit Condition(MutexLock& mutex)
    : mutex_(mutex)
  {
      /*
        MCHECK 在加锁和解锁操作中检查互斥锁的状态
        pthread_cond_init() 
        int pthread_cond_init(pthread_cond_t* cond, const pthread_condattr_t* attr);
        它有两个参数：

        cond：指向要初始化的条件变量的指针。
        attr：指向一个pthread_condattr_t类型的对象，表示条件变量的属性。如果为NULL，则使用默认属性。
        调用pthread_cond_init()函数可以创建一个条件变量，并初始化该条件变量的状态。
        在条件变量被初始化之后，该条件变量可以被用于在线程之间进行同步和通信。
        使用条件变量的主要方式是：一个线程在条件变量上等待另一个线程的通知，当满足某个条件时，通知线程唤醒等待的线程。
        条件变量的使用通常需要和互斥锁一起使用，以保证线程之间的同步和通信。

        需要注意的是，在使用条件变量时，为了避免竞争和死锁，常常需要加锁和解锁，以保证线程之间的正确协作。
        因此，在使用条件变量之前，通常需要先创建一个互斥锁，并在加锁和解锁时使用该互斥锁。
      */
      MCHECK(pthread_cond_init(&pcond_, NULL));
  }

  ~Condition()
  {
    MCHECK(pthread_cond_destroy(&pcond_));
  }

  void wait()
  {
    MutexLock::UnassignGuard ug(mutex_);
    MCHECK(pthread_cond_wait(&pcond_, mutex_.getPthreadMutex()));
  }

  // returns true if time out, false otherwise.
  bool waitForSeconds(double seconds);

  void notify()
  {
    MCHECK(pthread_cond_signal(&pcond_));
  }

  void notifyAll()
  {
    MCHECK(pthread_cond_broadcast(&pcond_));
  }

 private:
  MutexLock& mutex_;
  pthread_cond_t pcond_;
};

}  // namespace muduo

#endif  // MUDUO_BASE_CONDITION_H