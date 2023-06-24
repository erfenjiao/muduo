
#ifndef MUDUO_NET_SOCKETSOPS_H
#define MUDUO_NET_SOCKETSOPS_H

#include <arpa/inet.h>

namespace muduo
{
namespace net
{
namespace sockets
{

    ssize_t write(int sockfd, const void *buf, size_t count);
    ssize_t read (int sockfd, const void *buf, size_t count);

}  // namespace sockets
}  // namespace net
}  // namespace muduo

#endif  // MUDUO_NET_SOCKETSOPS_H