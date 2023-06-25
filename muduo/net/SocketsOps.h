
#ifndef MUDUO_NET_SOCKETSOPS_H
#define MUDUO_NET_SOCKETSOPS_H

#include <arpa/inet.h>

namespace muduo
{
namespace net
{
namespace sockets
{
    ///
    /// Creates a non-blocking socket file descriptor,
    /// abort if any error.
    int createNonblockingOrDie(sa_family_t family);

    int connect(int sockfd, const struct sockaddr* addr);
    void bindOrDie(int sockfd, const struct sockaddr* addr);
    void listenOrDie(int sockfd);
    int accept(int sockfd, struct sockaddr_in6* addr);

    ssize_t write(int sockfd, const void *buf, size_t count);
    ssize_t read (int sockfd, const void *buf, size_t count);
    ssize_t readv(int sockfd, const struct iovec*iov, int iovcnt);

    void close(int sockfd);
    void shutdownWrite(int sockfd);

    

}  // namespace sockets
}  // namespace net
}  // namespace muduo

#endif  // MUDUO_NET_SOCKETSOPS_H