

#include "../poller/PollPoller.h"
#include "../Channel.h"

#include "../../base/Logging.h"
#include "../../base/Types.h"


#include <assert.h>
#include <errno.h>
#include <poll.h>

using namespace muduo;
using namespace muduo::net;

PollPoller::PollPoller(EventLoop* loop)
  : Poller(loop)
{
}

PollPoller::~PollPoller() = default;

// virtual TimeStamp poll(int timeoutMs, ChannelList* activeChannels) = 0;
// Poller 的核心功能，调用 poll(2)获得当前活动的 IO 事件，然后填充调用方传入的 activeChannels，并返回 poll(2)return 的时刻
TimeStamp PollPoller::poll(int timeoutMs, ChannelList* activeChannels) {  

        /*
            __fortify_function __fortified_attr_access (__write_only__, 1, 2) int
            poll (struct pollfd *__fds, nfds_t __nfds, int __timeout)
            {
                return __glibc_fortify (poll, __nfds, sizeof (*__fds),
                            __glibc_objsize (__fds),
                            __fds, __nfds, __timeout);
            }

            这段代码定义了一个名为 `poll` 的函数，该函数使用了 `__fortify_function` 和 `__fortified_attr_access` 宏
            进行增强保护，其目的是防止缓冲区溢出攻击。

            `poll` 函数是用于轮询文件描述符的状态变化的系统调用，它接受
            一个指向结构体数组的指针 `__fds` 表示需要检测的文件描述符集合，
            一个 `nfds_t` 类型的整数 `__nfds` 表示需要检测的文件描述符数量，
            以及一个整数 `__timeout` 表示超时时间。该函数返回发生状态变化的文件描述符的数量。

            在函数实现中，调用了 `__glibc_fortify` 函数，该函数是 glibc 库提供的一个安全增强函数，
            用于检查内存操作是否越界。该函数接受多个参数，其中第一个参数是要进行安全检查的原始函数 `poll`，
            接下来的参数是传递给 `poll` 函数的参数。其作用是对传入的参数进行安全检查，确保不会发生缓冲区溢出等安全问题。
        */
        int numEvents = ::poll(&*pollfds_.begin(), pollfds_.size(), timeoutMs);

        // #define errno (*__errno_location ())
        int savedErrno = errno;

        TimeStamp now(TimeStamp::now());

        if( numEvents > 0) {
            LOG_TRACE << numEvents << " events happened";
            fillActiveChannels(numEvents, activeChannels);
        } 
        else if( numEvents == 0) {
            LOG_TRACE << "nothing happended";
        } 
        else {
            if (savedErrno != EINTR)
            {
                errno = savedErrno;
                LOG_SYSERR << "PollPoller::poll()";
            }
        }
        return now;
}


void PollPoller::fillActiveChannels(int numEvents,
                                    ChannelList* activeChannels) const{

    for(PollFdList::const_iterator pfd = pollfds_.begin() ; pfd != pollfds_.end() && numEvents > 0 ; ++pfd) {
        if(pfd->revents > 0) {
            --numEvents;
            // 从 fd 到 Channel* 的映射
            // typedef std::map<int, Channel*> ChannelMap;
            // ChannelMap channels_;
            // 注意： 在 Poller.h 中，ChannelMap 不能为 private
            ChannelMap::const_iterator ch = channels_.find(pfd->fd);
            assert(ch != channels_.end());

            // muduo::net::Channel *std::pair<const int, muduo::net::Channel *>::second
            // std::pair 是 C++ STL 中的一个模板类，用于存储两个不同类型的对象。
            // 声明一个指向 muduo::net::Channel 对象的指针变量，并将它赋值为一个 std::pair 对象的第二个成员变量 second 的地址。
            Channel* channel = ch->second;
            assert(channel->fd() == pfd->fd);

            // inline void muduo::net::Channel::set_revents(int revt)
            // void set_revents(int revt) {
            //    revent_ = revt;
            //}
            channel->set_revents(pfd->revents);

            activeChannels->push_back(channel);
        }
    }
}

/*
    updateChannel() 的主要功能是负责维护和更新 pollfds_ 数组
    添加新的Channel的复杂度是O(logN)
    更新已有的 Channel 的复杂度是 O(1)
    struct pollfd
  {
    int fd;			     File descriptor to poll.  
    short int events;    Types of events poller cares about.  
    short int revents;	 Types of events that actually occurred.  
  };
*/

void PollPoller::updateChannel(Channel* channel) {
    LOG_INFO << "PollPoller::updateChannel";
    Poller::assertInLoopThread();

    /*
        int fd() const {
            return fd_;      // 文件描述符
        }
        int events() const {
            return events_;  // IO 事件
        }
    */
    LOG_TRACE << "fd = " << channel->fd() << "events = " << channel->events();

    if(channel->index() < 0) {
        // a new one , add to pollfds_
        // muduo::net::Poller::ChannelMap muduo::net::Poller::channels_
        assert(channels_.find(channel->fd()) == channels_.end());
        struct pollfd pfd;

        pfd.fd      = channel->fd();
        // pfd.events  = channel->events();
        pfd.events  = static_cast<short>(channel->events());
        pfd.revents = 0;

        // typedef std::vector<pollfd> muduo::net::PollPoller::PollFdList
        // muduo::net::PollPoller::PollFdList muduo::net::PollPoller::pollfds_
        // struct pollfd pfd;
        pollfds_.push_back(pfd);

        int idx = static_cast<int>(pollfds_.size()) - 1;

        channel->set_index(idx);

        // muduo::net::Poller::ChannelMap muduo::net::Poller::channels_
        // 一个事件对应一个Map
        channels_[pfd.fd] = channel;


    } else {
        // update existing one
        /*
            更新已有的 Channel 的复杂度是 O(1)
                struct pollfd
            {
                int fd;			     File descriptor to poll.  
                short int events;    Types of events poller cares about.  
                short int revents;	 Types of events that actually occurred.  
            };
        */
        assert(channels_.find(channel->fd()) != channels_.end());
        assert(channels_[channel->fd()] == channel);

        int idx = channel->index();
        assert(idx <= 0 && idx < static_cast<int>(pollfds_.size()));

        struct pollfd& pfd = pollfds_[idx];
        assert(pfd.fd == channel->fd() || pfd.fd == -1);

        pfd.events = static_cast<short>(channel->events());

        pfd.revents = 0;

        if(channel->isNoneEvent()) {
            // ignore this pfd
            pfd.fd = -1;
        }
    }  // else
}

/*
Channel 类
private:
    void update();

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop* loop_;
    const int fd_;
    int events_;       // IO 事件
    int revent_;       // 目前活动的事件
    int index_;

    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
    EventCallback closeCallback_;

*/
void PollPoller::removeChannel(Channel * channel) {
    Poller::assertInLoopThread();
    LOG_TRACE << "fd = " << channel->fd();

    // typedef std::map<int, Channel*> ChannelMap;
    // muduo::net::Poller::ChannelMap muduo::net::Poller::channels_
    assert(channels_.find(channel->fd()) != channels_.end());
    assert(channels_[channel->fd()] == channel);
    assert(channel->isNoneEvent());

    int idx = channel->index();
    assert(0 <= idx && idx < static_cast<int>(pollfds_.size()));

    const struct pollfd& pfd = pollfds_[idx];
    (void)pfd;
    assert(pfd.fd == -channel->fd() - 1 && pfd.events == channel->events());

    size_t n = channels_.erase(channel->fd());
    assert(n == 1); (void)n;
    if (implicit_cast<size_t>(idx) == pollfds_.size()-1)
    {
        pollfds_.pop_back();
    }
    else
    {
        int channelAtEnd = pollfds_.back().fd;
        iter_swap(pollfds_.begin()+idx, pollfds_.end()-1);
        if (channelAtEnd < 0)
        {
        channelAtEnd = -channelAtEnd-1;
        }
        channels_[channelAtEnd]->set_index(idx);
        pollfds_.pop_back();
    }
}

/*

 class PollPoller : public Poller {
    public:
        PollPoller(EventLoop* loop);
        ~PollPoller() override;

        TimeStamp poll(int timeoutMs, ChannelList* activeChannels) override;

        void updateChannel(Channel* channel) override;

        void removeChannel(Channel* Channel) override;

    private:
        void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

        typedef std::vector<struct pollfd> PollFdList;
        
        PollFdList pollfds_;
}

Poller.h protected:

    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

    typedef std::vector<struct pollfd> PollFdList;
    // 从 fd 到 Channel* 的映射
    typedef std::map<int, Channel*> ChannelMap;

    EventLoop* ownerLoop_;
    //Poller::poll() 不会在每次调用poll(2)之前临时构造pollfd数组，而是将他们缓存起来(pollfds_)
    // typedef std::vector<pollfd> muduo::net::Poller::PollFdList
    PollFdList pollfds_;
    ChannelMap channels_;
*/
