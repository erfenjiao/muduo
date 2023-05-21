/*
    日志输出的核心组件之一。该类主要负责将用户写入的日志内容格式化并写入缓冲区中
    通过 operator<< 重载操作符实现对不同类型数据的格式化，并使用std::string存储格式化后的字符串
    每次写入日志时，LogStream会将格式化后的字符串追加到Buffer缓冲区中。

    除了能够将日志输出到Buffer缓冲区中，还提供了：获取日志缓冲区当前可用空间大小、判断缓冲区是否足够等

    LogStream类是一个轻量级的日志输出类，使用了流式编程的思想，可以自由地组合各种数据类型，并将它们转化为
    可读性较强的字符串。
    
    相比于其他的日志输出库，LogStream在性能上有着很大的优势，特别是在连续输出大量日志信息时，
    其高效的缓存管理机制可以减少内存申请和释放的次数，提升程序的整体性能。
*/

#ifndef MUDUO_BASE_LOGSTREAM_H
#define MUDUO_BASE_LOGSTREAM_H

#include <assert.h>
#include <string.h>

// #include "muduo/base/Types.h"
// #include "muduo/base/noncopyable.h"
// #include "muduo/base/StringPiece.h"

#include "Types.h"
#include "noncopyable.h"
#include "StringPiece.h"

namespace muduo
{
    namespace detail {
        const int KSmallBuffer = 4000;
        const int KLargeBuffer = 4000*1000;

        template<int SIZE>
        
        /*
            FixedBuffer类是一个固定大小的缓冲区。
            它主要用于存储日志输出时的格式化字符串。

            MUDUO 采用异步日志机制，即将日志内容写入一个线程安全的缓冲区中，再由专门的后台线程进行文件输出
            这样能大大提高日志输出效率和程序性能

            而FixedBuffer类就是用来作为日志缓冲区的核心组件之一。
            他的大小预先设定好，构造函数中会接收一个参数 size 来指定缓冲区的大小，
            而在运行过程中缓冲的大小不允许改变。


        */
        class FixedBuffer : noncopyable {
            public:
            FixedBuffer() : cur_(data_) {
                setCookie(cookieStart);
            }

            ~FixedBuffer() {
                setCookie(cookieEnd);
            }

            /*
                append() 将指定长度的数据追加到缓冲区中
            */
            void append(const char* buf, size_t len) {
                if(implicit_cast<size_t>(avail()) > len) {
                    memcpy(cur_, buf, len);
                    cur_ += len;
                }
            }

            const char* data() const { return data_; }
            int length() const { return static_cast<int>(cur_ - data_); }

            char* current() { return cur_; }
            int avail() const { return static_cast<int>(end() - cur_); }
            void add(size_t len) { cur_ += len; }

            /*
                reset() 把指针重置回缓冲区起始位置
            */
            void reset() { cur_ = data_; }
            void bzero() { memZero(data_, sizeof data_); }

            // for used by GDB
            const char* debugString();
            /*
                setCookie（）：
                没有实际作用，是留给用户自定义的函数接口，只是为了提供一个接口给给用户可以将任意数据保存在FixedBuffer对象中。
                
                void * 参数，即只想任意类型数据的指针。用户可以将自己的数据结构或者其他数据类型通过这个接口传入FixedBuffer对象，
                并在需要时获取和操作该数据。

                通常情况下这个函数不需要实现或调用，仅仅是充当一个可选的回调函数接口，用于MUDUO库的扩展
            */
            void setCookie(void (*cookie)()) {
                cookie_ = cookie; 
            }

            string toString() const { return string(data_, length()); }
            StringPiece toStringPiece() const { return StringPiece(data_, length()); }

            private:
            const char* end() const {
                return data_ + sizeof data_;
            }
            static void cookieStart();
            static void cookieEnd();

            void (*cookie_)();
            char data_[SIZE];
            char* cur_;
        };
    } // namespace detail

    class LogStream : noncopyable {
        typedef LogStream self;
        public:
        typedef detail::FixedBuffer<detail::KSmallBuffer> Buffer;

        self& operator<<(bool v) {
            buffer_.append(v ? "1" : "0", 1);
            return *this;
        }
        self& operator<<(short);
        self& operator<<(unsigned short);
        self& operator<<(int);
        self& operator<<(unsigned int);
        self& operator<<(long);
        self& operator<<(unsigned long);
        self& operator<<(long long);
        self& operator<<(unsigned long long);
        self& operator<<(const void*);

        self& operator<<(float v){
            *this << static_cast<double>(v);
            return *this;
        }
        self& operator<<(double);
        self& operator<<(char v) {
            buffer_.append(&v, 1);
            return *this;
        }
        self& operator<<(const char* str)
        {
            if (str)
            {
                buffer_.append(str, strlen(str));
            }
            else
            {
                buffer_.append("(null)", 6);
            }
            return *this;
        }

        self& operator<<(const unsigned char* str)
        {
            return operator<<(reinterpret_cast<const char*>(str));
        }

        self& operator<<(const string& v)
        {
            buffer_.append(v.c_str(), v.size());
            return *this;
        }

        self& operator<<(const StringPiece& v)
        {
            buffer_.append(v.data(), v.size());
            return *this;
        }

        self& operator<<(const Buffer& v)
        {
            *this << v.toStringPiece();
            return *this;
        }

        void append(const char* data, int len) { buffer_.append(data, len); }
        const Buffer& buffer() const { return buffer_; }
        void resetBuffer() { buffer_.reset(); }

        private:
        void staticCheck();

        template<typename T>
        void formatInteger(T);

        Buffer buffer_;

        static const int KMaxNumbericSize = 48;
    }; // class LogStream
    
    class Fmt // : noncopyable
    {
        public:
        template<typename T>
        Fmt(const char* fmt, T val);

        const char* data() const { return buf_; }
        int length() const { return length_; }

        private:
        char buf_[32];
        int length_;
    };

    inline LogStream& operator<<(LogStream& s, const Fmt& fmt)
    {
        s.append(fmt.data(), fmt.length());
        return s;
    }

    // Format quantity n in SI units (k, M, G, T, P, E).
    // The returned string is atmost 5 characters long.
    // Requires n >= 0
    string formatSI(int64_t n);

    // Format quantity n in IEC (binary) units (Ki, Mi, Gi, Ti, Pi, Ei).
    // The returned string is atmost 6 characters long.
    // Requires n >= 0
    string formatIEC(int64_t n);
        


} // namespace muduo

#endif