

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
      int numEvents = ::poll(&*pollfds_.begin(), pollfds_.size(), timeoutMs);
      int savedErrno = errno;

      TimeStamp now(TimeStamp::now());

      if( numEvents > 0) {
          LOG_TRACE << numEvents << " events happened";
          fillActiveChannels(numEvents, activeChannels);
      } else if( numEvents == 0) {
          LOG_TRACE << "nothing happended";
      } else {
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

        

    } else {
        // update existing one
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
