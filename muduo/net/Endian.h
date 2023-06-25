/*
这是一个网络编程库 Muduo 中的 endian.h 头文件，其中声明了一些用于网络字节序和主机字节序转换的函数，
具体作用如下：

hostToNetwork64()：将64位主机字节序的整数转换为网络字节序的整数。
hostToNetwork32()：将32位主机字节序的整数转换为网络字节序的整数。
hostToNetwork16()：将16位主机字节序的整数转换为网络字节序的整数。
networkToHost64()：将64位网络字节序的整数转换为主机字节序的整数。
networkToHost32()：将32位网络字节序的整数转换为主机字节序的整数。
networkToHost16()：将16位网络字节序的整数转换为主机字节序的整数。
这些函数都是使用系统提供的字节序转换函数来实现的。在 Linux 系统中，这些函数在头文件 endian.h 中定义。
需要注意的是，这些函数返回值的类型为无符号整数类型，分别为 uint64_t、uint32_t 和 uint16_t。
*/

#ifndef MUDUO_NET_ENDIAN_H
#define MUDUO_NET_ENDIAN_H

#include <stdint.h>
#include <endian.h>

namespace muduo
{
namespace net
{
namespace sockets
{
    // the inline assembler code makes type blur,
    // so we disable warnings for a while.
    /*
        使用了 GCC 编译器的一些预处理指令，用于暂时禁用某些类型转换的警告信息。

        将当前编译器的诊断状态压栈，以便后续可以恢复之前的状态。
    */ 
    #pragma GCC diagnostic push                        
    /*
        忽略 "Wconversion" 类型的警告信息，该警告类型通常会提示可能导致数据丢失或精度降低的隐式类型转换。
    */
    #pragma GCC diagnostic ignored "-Wconversion"     
    /*
        忽略 "Wold-style-cast" 类型的警告信息，该警告类型通常会提示使用了 C 风格的类型转换。
    */
    #pragma GCC diagnostic ignored "-Wold-style-cast"

    inline uint64_t hostToNetwork64(uint64_t host64)
    {
        return htobe64(host64);
    }

    inline uint32_t hostToNetwork32(uint32_t host32)
    {
        return htobe32(host32);
    }

    inline uint16_t hostToNetwork16(uint16_t host16)
    {
        return htobe16(host16);
    }

    inline uint64_t networkToHost64(uint64_t net64)
    {
        return be64toh(net64);
    }

    inline uint32_t networkToHost32(uint32_t net32)
    {
        return be32toh(net32);
    }

    inline uint16_t networkToHost16(uint16_t net16)
    {
        return be16toh(net16);
    }

    #pragma GCC diagnostic pop
}
}
}


#endif