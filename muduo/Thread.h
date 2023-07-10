#pragma once

#include <functional>
#include <thread>
#include <memory>
#include <unistd.h>
#include <string>
#include <atomic>

#include "noncopyable.h"

class Thread : noncopyable
{
    // thread start join
public:
    // 线程函数的函数类型
    using ThreadFunc = std::function<void()>;       // 线程函数如果想要带不同的类型-》知识点：绑定器和函数对象

    explicit Thread(ThreadFunc, const std::string &name = std::string());
    ~Thread();

    void start();
    void join();

    bool started() const { return started_; }
    pid_t tid() const    { return tid_; }
    const std::string& name() const { return name_;}

    static int numCreated() { return numCreated_;}

private:
    void setDefaultName();
    bool started_;
    bool joined_;
    // 不能直接写 std::thread thread_;  它会直接启动，所以我们要控制启动的时机，所以定义一个智能指针去封装它。
    std::shared_ptr<std::thread> thread_;

    pid_t tid_;

    ThreadFunc func_;     //存储线程函数
    std::string name_;     //每个线程都有自己的名字
    static std::atomic_int numCreated_;

};