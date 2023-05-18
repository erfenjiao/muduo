#ifndef MUDUO_BASE_LOGGING_H
#define MUDUO_BASE_LOGGING_H

#include "muduo/base/LogStream.h"
#include "muduo/base/TimeStamp.h"

#include <string>
#include <string.h>

namespace muduo {
    class TimeZone;

    class Logger {
        public:

        enum LogLevel {
            TRACE,
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL,
            NUM_LOG_LEVELS,
        };

        class SourceFile {
            public:
            template<int N>
            SourceFile(const char (&arr)[N]) : data_(arr), size(N-1) {
                const char* slash = strrchr(data_, '/');
                if(slash) {
                    data_ = slash + 1;
                    size_ -= static_cast<int>(data_ - arr);
                }
            }

            explicit SourceFile(const char* filename) : data_(filename) {
                const char* slash = strrchr(filename, '/');
                if(slash) {
                    data_ = slash + 1;
                }
                size_ = static_cast<int>(strlen(data_));
            }

            const char* data_;
            int size_;
        };

        Logger(SourceFile file, int line);
        Logger(SourceFile file, int line, LogLevel level);
        Logger(SourceFile file, int line, LogLevel level, const char* func);
        Logger(SourceFile file, int line, bool toAbort);
        ~Logger();

        LogStream& stream() {
            return impl_.stream_;
        }

        static LogLevel logLevel();
        static void setLogLevel(LogLevel level);

        typedef void (*OutputFunc)(const char* msg, int len);
        typedef void (*FlushFunc)();
        static void setOutput(OutputFunc);
        static void setFlush(FlushFunc);
        static void setTimeZone(const TimeZone& tz);

        private:

        /*
            Logger类定义了Impl类作为其内部类。
            这个Impl类主要起到了隐藏和保护Logger类的实现细节的作用，并允许Logger类的接口发生变化而不会破坏用户代码。

            Impl类通过将Logger类的接口分离为公共接口和实现接口两部分，将Logger类的实现隐藏在了Impl类中，
            避免外部代码对Logger类的实现进行干扰或者获取内部细节。

            同时，Impl类也是Logger的具体实现，它包含了写入日志文件、输出日志信息等核心函数，
            通过实例化Impl对象来完成Logger类的各项操作。
            
            使用Impl类有助于避免对用户接口的依赖性，提高程序的稳定性和可扩展性。
        */
        class Impl {
            public:
            typedef Logger::LogLevel LogLevel;
            Impl(LogLevel level, int old_errno, const SourceFile& file, int line);
            void formatTime();
            void finish();

            TimeStamp time_;
            LogStream stream_;
            LogLevel level_;
            int line_;
            SourceFile basename_;
        };
        Impl impl_;
    };

    extern Logger::LogLevel g_logLevel;

    inline Logger::LogLevel Logger::logLevel()
    {
        return g_logLevel;
    }

    #define LOG_TRACE if (muduo::Logger::logLevel() <= muduo::Logger::TRACE) \
        muduo::Logger(__FILE__, __LINE__, muduo::Logger::TRACE, __func__).stream()
    #define LOG_DEBUG if (muduo::Logger::logLevel() <= muduo::Logger::DEBUG) \
        muduo::Logger(__FILE__, __LINE__, muduo::Logger::DEBUG, __func__).stream()
    #define LOG_INFO if (muduo::Logger::logLevel() <= muduo::Logger::INFO) \
        muduo::Logger(__FILE__, __LINE__).stream()
    #define LOG_WARN muduo::Logger(__FILE__, __LINE__, muduo::Logger::WARN).stream()
    #define LOG_ERROR muduo::Logger(__FILE__, __LINE__, muduo::Logger::ERROR).stream()
    #define LOG_FATAL muduo::Logger(__FILE__, __LINE__, muduo::Logger::FATAL).stream()
    #define LOG_SYSERR muduo::Logger(__FILE__, __LINE__, false).stream()
    #define LOG_SYSFATAL muduo::Logger(__FILE__, __LINE__, true).stream()

    const char* strerror_tl(int savedErrno);

    // Taken from glog/logging.h
    //
    // Check that the input is non NULL.  This very useful in constructor
    // initializer lists.

    #define CHECK_NOTNULL(val) \
        ::muduo::CheckNotNull(__FILE__, __LINE__, "'" #val "' Must be non NULL", (val))

    // A small helper for CHECK_NOTNULL().
    template <typename T>
    T* CheckNotNull(Logger::SourceFile file, int line, const char *names, T* ptr)
    {
        if (ptr == NULL)
        {
            Logger(file, line, Logger::FATAL).stream() << names;
        }
        return ptr;
    }
} // namespace muduo

#endif