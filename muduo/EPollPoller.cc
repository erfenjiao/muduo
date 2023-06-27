#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "EPollPoller.h"
#include "Logger.h"
#include "Channel.h"

// 三种状态
const int kNew = -1;    // 某个channel还没添加至Poller          // channel的成员index_初始化为-1
const int kAdded = 1;   // 某个channel已经添加至Poller
const int kDeleted = 2; // 某个channel已经从Poller删除

EPollPoller::EPollPoller(EventLoop *loop) : Poller(loop),
                                            epollfd_(::epoll_create1(EPOLL_CLOEXEC)),
                                            events_(kInitEventListSize)     // vector<epoll_event>(16)
{
    if(epollfd_ < 0) {
        LOG_FATAL("epoll_create error : %d\n", errno);
    }
}

EPollPoller::~EPollPoller()
{
    ::close(epollfd_);
}

// epoll_wait
Timestamp EPollPoller::poll(int timeoutMs, ChannelList *activeChannels)
{
    // 由于频繁调用poll 实际上应该用LOG_DEBUG输出日志更为合理 当遇到并发场景 关闭DEBUG日志提升效率
    LOG_INFO("func=%s => fd total count:%lu\n", __FUNCTION__, channels_.size());

    // using EPollPoller::EventList = std::vector<epoll_event> 
    // EPollPoller::EventList EPollPoller::events_
    int numEvents = ::epoll_wait(epollfd_, &*events_.begin(), static_cast<int>(events_.size()), timeoutMs);
    int saveErrno = errno;      // errno 全局的
    Timestamp now(Timestamp::now());

    // 有发生事件的 fd
    if (numEvents > 0)  
    {
        LOG_INFO("%d events happend\n", numEvents);     // LOG_DEBUG最合理
        fillActiveChannels(numEvents, activeChannels);
        if (numEvents == events_.size())                // 扩容操作
        {
            events_.resize(events_.size() * 2);
        }
    }
    else if (numEvents == 0)
    {
        LOG_DEBUG("%s timeout!\n", __FUNCTION__);
    }
    else
    {
        if (saveErrno != EINTR)      // 不是中断
        {
            errno = saveErrno;        // 更新错误
            LOG_ERROR("EPollPoller::poll() error!");
        }
    }
    return now;
}

// channel update remove => EventLoop updateChannel removeChannel => Poller updateChannel removeChannel
/*
    poller.poll() 通过监听到 epoll_wait fd 监听到 channel 发生的事件，.
                    EventLoop  =>  poller.poll()
        ChannelList             Poller
                                ChannelMap<fd, channel*>
*/
void EPollPoller::updateChannel(Channel *channel)
{
    const int index = channel->index();
    LOG_INFO("func=%s => fd=%d events=%d index=%d\n", __FUNCTION__, channel->fd(), channel->events(), index);
    if(index == kNew || index == kDeleted)     // 从来没有添加到poller 中，或者已经从poller中删除
    {
        if(index == kNew)                      // 从来没有添加到poller 中
        {
            int fd = channel->fd();
            channels_[fd] = channel;
        }
        channel->set_index(kAdded);
        update(EPOLL_CTL_ADD, channel);        // 注册
    }
    else                                       // channel已经在Poller中注册过了
    {
        int fd = channel->fd();
        if(channel->isNoneEvent())             // 对任何事件都不感兴趣
        {
            update(EPOLL_CTL_DEL, channel);    // 删除
            channel->set_index(kDeleted);
        }
        else                                   // 更新
        {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

// 从Poller中删除channel,如果向 ChannelList 中注册过，也需要删除
/*
                    EventLoop
        ChannelList             Poller
                                ChannelMap<fd, channel*>
*/
void EPollPoller::removeChannel(Channel *channel)
{
    // 取得 fd
    int fd = channel->fd();

    LOG_INFO("func=%s => fd=%d\n", __FUNCTION__, fd);

    int index = channel->index();
    channels_.erase(fd);

    if(index == kAdded)
    {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->set_index(kNew);
}

// 填写活跃的连接
void EPollPoller::fillActiveChannels(int numEvents, ChannelList *activeChannels) const
{
    for(int i = 0; i < numEvents ; i++)
    {
        Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->set_revents(events_[i].events);       // 设置发生的事件
        activeChannels->push_back(channel);            // EventLoop 就拿到了它的 Poller 给它返回的所有发生事件的channel列表了
    }
}

/*
    更新channel通道 其实就是调用 epoll_ctl add/mod/del
    int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
    四个参数：events fd中的事件，operator操作类型， fd 现在需要更改的事件 

    typedef union epoll_data {
        void        *ptr;        // 携带fd绑定的参数数据
        int          fd;
        uint32_t     u32;
        uint64_t     u64;
    } epoll_data_t;

    struct epoll_event {
        uint32_t     events;       Epoll events
        epoll_data_t data;         User data variable 
    };

*/
void EPollPoller::update(int operation, Channel *channel)
{
    epoll_event event;
    int fd = channel->fd();

    event.events   = channel->events();
    event.data.fd  = fd;    // channel->fd()
    event.data.ptr = channel;

    if(::epoll_ctl(epollfd_, operation, fd, &event) < 0)
    {
        LOG_ERROR("epoll_ctl del error:%d\n", errno);
    }  
    else
    {
        LOG_FATAL("epoll_ctl add/mod error:%d\n", errno);
    }
}
