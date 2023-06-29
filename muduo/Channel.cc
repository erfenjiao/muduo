#include <sys/epoll.h>

#include "Channel.h"
#include "EventLoop.h"
#include "Logger.h"

/*
    #define EPOLLIN EPOLLIN
        EPOLLPRI = 0x002,
    #define EPOLLPRI EPOLLPRI
        EPOLLOUT = 0x004,
    #define EPOLLOUT EPOLLOUT
        EPOLLRDNORM = 0x040,
*/
const int Channel::kNoneEvent  = 0;
const int Channel::kReadEvent  = EPOLLIN | EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;

// EventLoop: ChannelList Poller
Channel::Channel(EventLoop *loop, int fd)
    : loop_(loop)      // 每一个 channel 都有一个 loop，将这个 loop 记下来
    , fd_(fd)
    , events_(0)
    , revents_(0)
    , index_(-1)   // -1 const int kNew = -1;    某个channel还没添加至Poller，channel的成员index_初始化为-1
    , tied_(false)
{
}

Channel::~Channel()
{
}

// channel的tie方法什么时候调用过?  TcpConnection => channel
/**
 * TcpConnection中注册了Chnanel对应的回调函数，传入的回调函数均为TcpConnection
 * 对象的成员方法，因此可以说明一点就是：Channel的结束一定早于TcpConnection对象！
 * 此处用tie去解决TcoConnection和Channel的生命周期时长问题，从而保证了Channel对
 * 象能够在TcpConnection销毁前销毁。
 **/
void Channel::tie(const std::shared_ptr<void>& obj)   // 智能指针
{
    tie_  = obj;
    tied_ = true;   //绑定过，置成 true
}

/**
 * 当改变 channel 所表示的 fd 的 events事件后，update 负责在 poller 里面更改 fd 相应的事件 epoll_ctl
 * EventLoop => ChannelList  Poller
 **/
void Channel::update() 
{
    // 通过 channel 所属的 eventloop ，调用 poller 的相应方法，注册 fd 的 events 事件
    // add code...
    // loop_->updateChannel(this);  直接传入channel，通过 eventloop 进行操作。
}


// 在channel 所属的 EventLoop 中把当前的 channel 删除掉
void Channel::remove()
{
    // add code...
    // loop_->removeChannel(this);
}

// fd 得到 Poller 通知以后，处理事件 handleEvent ,在 EventLoop::loop()中调用 
void Channel::handleEvent(Timestamp receiveTime)
{
    if(tied_)
    {
        std::shared_ptr<void> guard = tie_.lock();
        if(guard)
        {
            handleEventWithGuard(receiveTime);
        }
    }
    else
    {
        handleEventWithGuard(receiveTime);
    }
}


/*
    WithGuard 受保护的
    根据接收到的事件，执行相应的回调操作
    using EventCallback = std::function<void()>;  
    // 只读事件的回调
    using ReadEventCallback = std::function<void(Timestamp)>;
*/
void Channel::handleEventWithGuard(Timestamp receiveTime)
{
    LOG_INFO("channel handleEvent revents:%d\n", revents_);
    
    if((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
    {
        if(closeCallback_)
        {
            closeCallback_();  // 发生异常
        }
    }

    if(revents_ & EPOLLERR)
    {
        if(errorCallback_)
        {
            errorCallback_();
        }
    }

    if(revents_ & (EPOLLIN | EPOLLPRI))
    {
        if(readCallback_)
        {
            readCallback_(receiveTime);  // using ReadEventCallback = std::function<void(Timestamp)>;
        }
    }

    if(revents_ & EPOLLOUT)
    {
        if(writeCallback_)
        {
            writeCallback_();
        }
    }

}

