#pragma once

#include <functional>
#include <vector>
#include <atomic>
#include <memory>
#include <mutex>

#include "noncopyable.h"
#include "Timestamp.h"
#include "CurrentThread.h"

class Channel;
class Poller;

/*
    EventLoop    对应 Reactor
    epoll poller 对应 Demultiplex
*/

// 事件循环类 主要包含了两个大模块 Channel Poller(epoll的抽象)
class EventLoop : noncopyable
{
public:
    using Functor = std::function<void()>;

    EventLoop();
    ~EventLoop();

    // 开启事件循环
    void loop();
    // 退出事件循环
    void quit();

    Timestamp pollReturnTime() const { pollRetureTime_;}

    
    void runInLoop(Functor cb);                // 在当前loop中执行
    void queueInLoop(Functor cb);              // 把上层注册的回调函数cb放入队列中 唤醒loop所在的线程执行cb

    void wakeup();                             // 通过eventfd唤醒loop所在的线程

    // EventLoop的方法 => Poller的方法
    void updateChannel(Channel *channel);
    void removeChannel(Channel *channel);
    bool hasChannel(Channel *channel);

    // 判断EventLoop对象是否在自己的线程里
    bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }  // threadId_为EventLoop创建时的线程id CurrentThread::tid()为当前线程id，没有在，则 queueInLoop ，去执行相关的回调操作。

private:
    void handleRead();
    void doPendingFunctors();

    using ChannelList  = std::vector<Channel*>;

    bool looping_;                             // atomic , 通过 CAS 实现
    std::atomic_bool quit_;                    // 标识退出 loop 循环, 一般在其他线程调用
  //std::atomic_bool callingPendingFunctors_;  // 标识当前 loop 是否有需要执行的回调操作

    const pid_t threadId_;                     // 记录当前 EventLoop 是被哪个线程 id 创建的 即标识了当前 EventLoop 的所属线程id , 判断 EventLoop 在不在它自己的线程里面

    Timestamp pollRetureTime_;                 // Poller返回发生事件的 Channels 的时间点

    std::unique_ptr<Poller> poller_;           // 会自动析构

    int wakeupFd_;                             // 使用 eventfd() 创建， 作用：当 mainLoop 获取一个新用户的 Channel 需通过轮询算法选择一个 subLoop 通过该成员唤醒 subLoop 处理 Channel
    std::unique_ptr<Channel> wakeupChannel_;   // wakeupFd_ 存储在这个 channel 里面

    ChannelList activeChannels_;
    Channel* currentActiveChannel_;

    std::atomic_bool callingPendingFunctors_; // 标识当前 loop 是否有需要执行的回调操作
    std::vector<Functor> pendingFunctors_;    // 存储 loop 需要执行的所有回调操作
    std::mutex mutex_;                        // 互斥锁 用来保护上面 vector 容器的线程安全操作
};

/*
    eventfd()
*/