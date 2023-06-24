#include "SocketsOps.h"

#include "../base/Logging.h"
#include "../base/Types.h"
#include "Endian.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>    // snprintf
#include <sys/socket.h>
#include <sys/uio.h>  // readv
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

using namespace muduo;
using namespace muduo::net;

namespace{




}

ssize_t sockets::write(int sockfd, const void* buf, size_t count){
    return ::write(sockfd, buf, count);
}

ssize_t sockets::read(int sockfd, void *buf, size_t count)
{
  return ::read(sockfd, buf, count);
}