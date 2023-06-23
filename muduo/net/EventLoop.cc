// #include "muduo/net/EventLoop.h"
// #include "muduo/net/Channel.h"
// #include "muduo/net/Poller.h"

// #include "muduo/base/Logging.h"
// #include "muduo/base/CurrentThread.h"

#include "EventLoop.h"
#include "Channel.h"
#include "Poller.h"
#include "TimerId.h"
#include "TimerQueue.h"

#include "../base/Logging.h"
#include "../base/CurrentThread.h"
#include "../base/Mutex.h"

#include <algorithm>

#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <sys/eventfd.h>

using namespace muduo;
using namespace muduo::net;

namespace
{
    __thread EventLoop* t_loopInThisThread = 0;

    const int kPollTimeMs = 10000;

    int createEventfd()
    {
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0)
    {
        LOG_SYSERR << "Failed in eventfd";
        abort();
    }
    return evtfd;
    }

    #pragma GCC diagnostic ignored "-Wold-style-cast"
    class IgnoreSigPipe
    {
    public:
        IgnoreSigPipe()
        {
            ::signal(SIGPIPE, SIG_IGN);
            // LOG_TRACE << "Ignore SIGPIPE";
        }
    };
    #pragma GCC diagnostic error "-Wold-style-cast"

    IgnoreSigPipe initObj;
}  // namespace

/* 
    返回 EventLoop 对象 
*/
EventLoop* EventLoop::getEventLoopOfCurrentThread(){
    return t_loopInThisThread;
}

/*
    构造函数
*/
EventLoop::EventLoop():looping_(false), 
                        quit_(false),
                        eventHandling_(false),
                        callingPendingFunctors_(false),
                        iteration_(0),
                        threadId_(CurrentThread::tid()),
                        poller_(Poller::newDefaultPoller(this)),
                        timerQueue_(new TimerQueue(this)),
                        wakeupFd_(createEventfd()),
                        wakeupChannel_(new Channel(this, wakeupFd_)),
                        currentActiveChannel_(NULL)
                         {
    LOG_TRACE << "EventLoop created " << this << " in thread " << threadId_;

    if(t_loopInThisThread) {
        LOG_FATAL << "Another EventLoop " << t_loopInThisThread << " exists in this thread " << threadId_;
    }
    else {
        t_loopInThisThread = this;
    }
//     wakeupChannel_->setReadCallback(
//       std::bind(&EventLoop::handleRead, this));
//   // we are always reading the wakeupfd
//   wakeupChannel_->enableReading();
}

EventLoop::~EventLoop() {
    LOG_DEBUG << "EventLoop " << this << " of thread " << threadId_
            << " destructs in thread " << CurrentThread::tid();
    // wakeupChannel_->disableAll();
    // wakeupChannel_->remove();
    assert(!looping_);
    t_loopInThisThread = NULL;
}

/*
    事件循环
    调用Poller::poll() 获得当前活动事件的 Channel 列表，
    然后依次调用每个 Channel 的 handleEvent() 函数
*/
void EventLoop::loop() {
    assert(!looping_);
    assertInLoopThread();

    looping_ = true;
    quit_ = false;
    // LOG_TRACE << "EventLoop " << this << " start looping";

    /*
        新增了quit() 成员函数，还加了几个数据成员，并在构造函数里初始化它们
        EventLoop 通过 scoped_ptr 来间接持有 Poller，因此 EventLoop.h 中不必包含 Poller.h
    */
    while(!quit_) {
        activeChannels_.clear();
        poller_->poll(kPollTimeMs, &activeChannels_);

        for(ChannelList::iterator it = activeChannels_.begin() ; it != activeChannels_.end() ; ++it) {

            (*it)->handleEvent();
        }
    }

    LOG_TRACE << "EventLoop" << this << " stop looping";
    looping_ = false;
}

void EventLoop::abortNotLoopThread() {
    LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop" << this
                << "was created in threadId_ = " << threadId_
                << ", current thread id = " << CurrentThread::tid(); 
}

/*
    检查断言之后调用Poller::updateChannel()
*/
void EventLoop::updateChannel(Channel* channel) {
    LOG_INFO << "EventLoop::updateChannel - channel:" << channel;
    assert(channel->ownerLoop() == this);
    assertInLoopThread();

    //poller_->updateChannel(channel);
    if (poller_) {
        poller_->updateChannel(channel);
    }else {
        LOG_INFO << "poller_ 是空指针";
    }
}



void EventLoop::removeChannel(Channel* channel)
{
    assert(channel->ownerLoop() == this);
     assertInLoopThread();
    if (eventHandling_)
    {
        assert(currentActiveChannel_ == channel ||
            std::find(activeChannels_.begin(), activeChannels_.end(), channel) == activeChannels_.end());
    }
    poller_->removeChannel(channel);
}

bool EventLoop::hasChannel(Channel* channel)
{
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    return poller_->hasChannel(channel);
}


void EventLoop::quit() {
    quit_ = true;
    if(!isInLoopThread()) {
        //wakeup();
    }
}

void EventLoop::wakeup() {
    uint64_t one = 1;
    ssize_t n = sockets::write(wakeupFd_, &one, sizeof one);
    if(n != sizeof one) {
        LOG_ERROR << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
    }
}

void EventLoop::runInLoop(Functor cb) {
    if(isInLoopThread()){
        cb();
    }
    else{
        queueInLoop(std::move(cb));
    }
}

// void queueInLoop(Functor cb);
void EventLoop::queueInLoop(Functor cb) {
    {
        MutexLockGuard lock(mutex_);
        pendingFunctors_.push_back(std::move(cb));
    }
    if (!isInLoopThread() || callingPendingFunctors_)
    {
        wakeup();
    }

}

TimerId EventLoop::runAt(TimeStamp time, TimerCallback cb) {
    return timerQueue_->addTimer(cb, time, 0.0);
}

TimerId EventLoop::runAfter(double delay, TimerCallback cb){
    TimeStamp time(addTime(TimeStamp::now(), delay));
    return runAt(time, cb);
}

TimerId EventLoop::runEvery(double interval, TimerCallback cb){
    TimeStamp time(addTime(TimeStamp::now(), interval));
    /*
        std::move
        用于将对象转移或复制到另一个位置。它实际上并不执行任何操作，而是通过返回指向输入参数的右值引用来告诉编译器该对象可以被移动。
    */
    return timerQueue_->addTimer(std::move(cb), time, interval);
}

