/*
    用于 accept(2)新TCP连接，并通过回调通知使用者
    是内部class，供TcpServer使用，生命周期由后者控制
*/

#ifndef MUDUO_NET_ACCEPTOR_H
#define MUDUO_NET_ACCEPTOR_H

#include <functional>

#include "Channel.h"
#include "Socket.h"

namespace muduo
{
namespace net
{

class EventLoop;
class InetAddress;

///
/// Acceptor of incoming TCP connections.
///


}  // namespace net
}  // namespace muduo

#endif  // MUDUO_NET_ACCEPTOR_H