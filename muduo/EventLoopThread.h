#pragma one

#include"noncopyable.h"
#include"Thread.h"

#include<functional>
#include<mutex>
#include<condition_variable>

class EventLoop;

class EventLoopThread : noncopyable
{
public:
    // 线程初始化回调
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(), const std::string& name = std::string());
    ~EventLoopThread();

    EventLoop *startLoop();

private:
    void threadFunc();
    EventLoop* loop_;        // 一个 loop
    bool exiting_;
    Thread thread_;          // 一个thread
    std::mutex mutex_;
    std::condition_variable cond_;
    ThreadInitCallback callback_;
};