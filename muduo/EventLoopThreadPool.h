#pragma one
#include "noncopyable.h"

#include <functional>
#include <string>
#include <vector>
#include <memory>

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool : noncopyable
{
public:
    // 也是 EventLoopThread.h 中定义的，因为Pool管理它
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    EventLoopThreadPool(EventLoop* baseLoop, const std::string& nameArg);

    // 析构不做任何事情
    ~EventLoopThreadPool();

    // 设置底层线程数量
    void setThreadNum(int numThreads) { numThreads_ = numThreads; }

    // 初始化回调
    void start(const ThreadInitCallback& cb = ThreadInitCallback());

    // 如果工作在多线程中，baseLoop_(mainLoop) 会默认以轮询的方式分配 Channel 给 subLoop
    EventLoop* getNextLoop();

    std::vector<EventLoop*> getAllLoops();

    bool started() const { return started_;}
    const std::string name() const { return name_; }
private:
    EventLoop* baseLoop_;  // EventLoop loop;用户使用的线程，作为新用户的连接，和已连接用户的读写事件
    std::string name_;
    bool started_;
    int numThreads_;
    int next_;
    std::vector<std::unique_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> loops_; 
};

