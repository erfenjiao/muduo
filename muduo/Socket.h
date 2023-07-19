#pragma once

#include "noncopyable.h"

class InetAddress;

// 封装socket fd
class Socket : noncopyable
{
public:
    explicit Socket(int sockfd)
    : sockfd_(sockfd)
    {}

    ~Socket();

    int fd() const { return sockfd_; }
    void bindAddress(const InetAddress &localaddr);
    void listen();
    int accept(InetAddress* peeraddr);

    void shutdownWrite();

    // 更改 TCP 选项
    void setTcpNoDelay(bool on);   // 直接发送，不进行缓冲
    void setReuseAddr(bool on);   
    void setReusePort(bool on);
    void setKeepAlive(bool on);
private:
    const int sockfd_;
};