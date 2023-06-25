#include "InetAddress.h"

#include "../base/Logging.h"
#include "Endian.h"
#include "SocketsOps.h"

#include <netdb.h>
#include <netinet/in.h>

// INADDR_ANY use (type)value casting.
#pragma GCC diagnostic ignored "-Wold-style-cast"
static const in_addr_t kInaddrAny = INADDR_ANY;
static const in_addr_t kInaddrLoopback = INADDR_LOOPBACK;
#pragma GCC diagnostic error "-Wold-style-cast"

using namespace muduo;
using namespace muduo::net;

/*
确保InetAddress类可以完整地转换为sockaddr_in6结构体，
因为在网络编程中，常常需要将IP地址与端口号封装成一个sockaddr_in6结构体，并传递给Socket API函数进行网络通信。
*/
static_assert(sizeof(InetAddress) == sizeof(struct sockaddr_in6),
              "InetAddress is same size as sockaddr_in6");
static_assert(offsetof(sockaddr_in, sin_family) == 0, "sin_family offset 0");
static_assert(offsetof(sockaddr_in6, sin6_family) == 0, "sin6_family offset 0");
static_assert(offsetof(sockaddr_in, sin_port) == 2, "sin_port offset 2");
static_assert(offsetof(sockaddr_in6, sin6_port) == 2, "sin6_port offset 2");

InetAddress::InetAddress(uint16_t portArg, bool loopbackOnly, bool ipv6){
    static_assert(offsetof(InetAddress, addr6_) == 0, "addr6_ offset 0");
    static_assert(offsetof(InetAddress, addr_) == 0, "addr_ offset 0");

    if(ipv6){
        memZero(&addr6_, sizeof addr6_);
        addr6_.sin6_family = AF_INET;
        in6_addr ip = loopbackOnly ? in6addr_loopback : in6addr_any;
        addr6_.sin6_addr = ip;
        addr6_.sin6_port = sockets::hostToNetwork16(portArg);
    }
    else{
        memZero(&addr_, sizeof addr_);
        addr_.sin_family = AF_INET;
        in_addr_t ip = loopbackOnly ? kInaddrLoopback : kInaddrAny;
        addr_.sin_addr.s_addr = sockets::hostToNetwork32(ip);
        addr_.sin_port = sockets::hostToNetwork16(portArg);
    }
}
/*
    用于创建一个网络地址对象，它接受一个IP地址字符串、一个端口号和一个bool型参数，表示是否使用IPv6。
    这个函数首先检查是否需要使用IPv6，如果是，
    则调用sockets::fromIpPort()函数将IP地址和端口号转换为IPv6格式，并存储在addr6_变量中；

    否则，调用同样的函数将IP地址和端口号转换为IPv4格式，并存储在addr_变量中。
*/
InetAddress::InetAddress(StringArg ip, uint16_t portArg, bool ipv6)
{
    if (ipv6 || strchr(ip.c_str(), ':'))
    {
        memZero(&addr6_, sizeof addr6_);
        //SocketsOps.cc
        sockets::fromIpPort(ip.c_str(), portArg, &addr6_);
    }
    else
    {
        memZero(&addr_, sizeof addr_);
        sockets::fromIpPort(ip.c_str(), portArg, &addr_);
    }
}

string InetAddress::toIp() const{
    char buf[64] = "";
    sockets::toIp(buf, sizeof buf, getSockAddr());
    return buf;
}