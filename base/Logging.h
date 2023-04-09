#ifndef MUDUO_BASE_LOGGING_H
#define MUDUO_BASE_LOGGING_H

#include <string>
#include <string.h>

namespace muduo {
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

        Logger();

        ~Logger();
    };
}

#endif