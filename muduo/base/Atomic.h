#ifndef MUDUO_BASE_ATOMIC_H
#define MUDUO_BASE_ATOMIC_H

// #include "muduo/base/noncopyable.h"
#include "noncopyable.h"

#include <stdint.h>

namespace muduo {
    namespace detail {
        template<typename T>
        class AtomicIntegerT : noncopyable {
            public:
            AtomicIntegerT() : value_(0) {}

            T get() {
                /*
                    __sync_val_compare_and_swap()函数是一个原子比较和交换操作，用于实现多线程间的同步，也就是CAS算法。
                    该函数接受三个参数：一个指针、一个旧值和一个新值。

                    具体来说，__sync_val_compare_and_swap()会首先读取指针所指向的内存地址中的值，
                    如果该值等于旧值，则将新值写入该内存地址，否则不做任何操作。
                    在这个过程中，如果有其他线程同时修改了该内存地址中的值，那么当前线程会重新读取该值，并尝试再次进行比较和修改，直到成功为止。

                    通过使用CAS算法，可以避免多个线程同时访问同一个共享变量时发生竞态条件问题，从而实现线程安全的操作。
                    在muduo网络库中，Atomic类中的__sync_val_compare_and_swap()函数被广泛应用于各种场景，例如实现线程池任务队列的同步等。
                */
                return __sync_val_compare_and_swap(&value_, 0, 0);
            }

            T getAndAdd(T x) {
                /*
                    It is used to perform an atomic addition operation on a variable and return the new value.
                */
                return __sync_fetch_and_add(&value_, x);
            }

            T addAndGet(T x) {
                return getAndAdd(x) + x;
            }

            T incrementAndGet() {
                return addAndGet(1);
            }

            T decrementAndGet() {
                return addAndGet(-1);
            }

            void add(T x) {
                getAndAdd(x);
            }

            void increment() {
                incrementAndGet();
            }

            void decrement() {
                decrementAndGet();
            }

            T getAndGet(T newValue) {
                return __sync_lock_test_and_set(&value_, newValue);
            }

            private:
            volatile T value_;
        };  
    } // namespace detail

    typedef detail::AtomicIntegerT<int32_t> AtomicInt32;
    typedef detail::AtomicIntegerT<int64_t> AtomicInt64;
}

#endif