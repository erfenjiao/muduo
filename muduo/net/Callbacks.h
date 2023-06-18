
#ifndef MUDUO_NET_CALLBACKS_H
#define MUDUO_NET_CALLBACKS_H

#include "../base/TimeStamp.h"

#include <functional>
#include <memory>

/*
    Callbacks.h 用于定义网络编程中的各种回调类型。
    
    设计思路可以总结如下：
    1. 使用函数对象（std::function）为回调提供通用接口。
    2. 定义与各种网络事件相关的回调类型，例如连接建立、消息接收、写完成、高水位标记和连接关闭等。
    3. 使用 shared_ptr 管理 TcpConnection 对象的生命周期。
    4. 提供 down_pointer_cast() 和 get_pointer() 等实用函数，以在不同智能指针类型之间进行转换。
    5. Callbacks.h 头文件提供了一组 typedefs，用于常用的回调函数签名，包括 ConnectionCallback、CloseCallback、
    MessageCallback、WriteCompleteCallback、HighWaterMarkCallback 和 TimerCallback 等。
    6. defaultConnectionCallback() 和 defaultMessageCallback() 函数分别定义了新连接建立或现有连接上接收数据时的默认行为。

    回调是什么？
    回调在网络库中的作用是处理事件驱动的编程模型。网络库通常使用异步 IO 模型，当某个网络事件发生时（比如连接建立、数据到达等），
    网络库会通过回调函数通知应用程序，并由应用程序进行进一步处理。
    例如，在 muduo 库中，当一个 TCP 连接建立时，会调用 ConnectionCallback 回调函数；当有数据到达时，会调用 MessageCallback 回调函数。
    应用程序可以根据需要重写这些回调函数，实现自己的业务逻辑。
    通过回调函数，应用程序可以方便地处理各种网络事件，并实现自定义的业务逻辑。
*/

namespace muduo
{
    /*
        使用了 C++11 中的 std::placeholders 命名空间，用于创建占位符对象。
        在一个函数或者函数对象中，可能会有一些参数暂时不知道具体的值，可以使用占位符来代替这些参数，
        等到函数被调用时再传入具体的值。
        例如，在使用 STL 中的 std::bind() 函数时，如果需要绑定函数对象的某些参数，但还无法确定具体值，就可以使用占位符。
        _1 表示第一个参数，_2 表示第二个参数，以此类推。当实际调用 bind() 返回的函数对象时，将使用传入的参数依次替换占位符的位置。
        因此，这段代码的作用是使用 using 关键字，将占位符 _1、_2、_3 引入当前代码所在的命名空间，以便在后续的代码中直接使用这些占位符。
    */
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;

    /*
        定义了一个名为 get_point 的函数模板，它接受一个类型为 std::shared_ptr<T> 
        的智能指针参数，并返回该智能指针所管理的对象的原始指针

        typename 的作用是告诉编译器 std::shared_ptr<T> 中的 T 是一个类型名（type name），
        而不是一个非类型成员（non-type member）。

        这是因为 std::shared_ptr<T> 中的 T 在模板实例化前是未知的，
        编译器需要通过 typename 来确定 T 是一个类型名，以便正确解析代码。
    */
    template<typename T>
    inline T* get_point(const std::shared_ptr<T>& ptr){
        return ptr.get();
    }

    template<typename T>
    inline T* get_point(const std::unique_ptr<T>& ptr) {
        return ptr.get();
    }

    /*
        定义了一个函数模板down_pointer_cast，用于实现shared_ptr的指针类型转换操作。
        该函数的作用类似于dynamic_cast操作符
    */
    template<typename To, typename From>
    inline ::std::shared_ptr<To> down_point_cast(const ::std::shared_ptr<From>& f){
        /*
            if语句中，使用了一个技巧来产生编译器错误，以防止在不支持down_pointer_cast的情况下进行无效的转换操作。
            具体实现方式是通过将From隐式转换为To（即static_cast<To*>(static_cast<From*>(0))），
            然后将结果0强制转换为From和To两个指针类型，从而使编译器产生一个错误信息。
        */
        if(false) {
            implicit_cast<From*, To*>(0);
        }

        #ifndef NDEBUG
            assert(f == NULL || dynamic_cast<To*>(get_point(f)) != NULL);
        #endif

        return ::std::static_pointer_cast<To>(f);
    }


    namespace net
    {
        class Buffer;
        class TcpConnection;
        typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
        
        typedef std::function<void()> TimerCallback;
        typedef std::function<void (const TcpConnectionPtr&)> ConnectionCallback;
        typedef std::function<void (const TcpConnectionPtr&)> CloseCallback;
        typedef std::function<void (const TcpConnectionPtr&)> WriteCompleteCallback;
        typedef std::function<void (const TcpConnectionPtr&, size_t)> HighWaterMarkCallback;

        // the data has been read to (buf, len)
        typedef std::function<void (const TcpConnectionPtr&,
                                    Buffer*,
                                    TimeStamp)> MessageCallback;

        void defaultConnectionCallback(const TcpConnectionPtr& conn);
        void defaultMessageCallback(const TcpConnectionPtr& conn,
                                    Buffer* buffer,
                                    TimeStamp receiveTime);


        
    } // namespace net
    
} // namespace muduo


#endif  //MUDUO_NET_CALLBACKS_H