#ifndef MUDUO_NET_CHANNEL_H
#define MUDUO_NET_CHANNEL_H

// 核心：事件分发机制

#include <functional>

#include "../base/noncopyable.h"
#include "../base/TimeStamp.h"

namespace muduo
{
    namespace net
    {
        class EventLoop;

        class Channel{
            public:
            // 回调
            typedef std::function<void()> EventCallback;
            typedef std::function<void(TimeStamp)> ReadEventCallback;

            
            Channel(EventLoop* loop, int fd);
            ~Channel();

            // 核心
            void handleEvent();

            void setReadCallback(ReadEventCallback cb)
            { readCallback_ = std::move(cb); }

            void setWriteCallback(EventCallback cb)
            { writeCallback_ = std::move(cb); }

            void setCloseCallback(EventCallback cb)
            { closeCallback_ = std::move(cb); }

            void setErrorCallback(EventCallback cb)
            { errorCallback_ = std::move(cb); }


            int fd() const {
                return fd_;
            }

            int events() const {
                return events_;
            }

            void set_revents(int revt) {
                revent_ = revt;
            }

            bool isNoneEvent() const {
                return events_ == kNoneEvent;
            }

            void enableReading() {
                events_ |= kReadEvent;
                update();
            }

            // for Poller
            int index() {
                return index_;
            }
            void set_index(int idx) {
                index_ = idx;
            }

            string reventsToString() const;
            string eventsToString() const;

            EventLoop* ownerLoop() {
                return loop_;
            }

            private:
            static string eventsToString(int fd, int ev);

            void update();

            /* 必须初始化。在 cc 中 */
            static const int kNoneEvent;
            static const int kReadEvent;
            static const int kWriteEvent;

            EventLoop* loop_;
            const int fd_;
            int events_;       // IO 事件
            int revent_;       // 目前活动的事件
            int index_;

            bool eventHandling_;
            bool addedToLoop_;

            ReadEventCallback readCallback_;
            EventCallback writeCallback_;
            EventCallback errorCallback_;
            EventCallback closeCallback_;

        };
    } // namespace net
    
} // namespace Channel


#endif