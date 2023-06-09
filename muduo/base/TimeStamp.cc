#include "TimeStamp.h"
#include "Logging.h"

#include <sys/time.h>
#include <stdio.h>

#include <inttypes.h>

using namespace muduo;

// static_assert(sizeof(TimeStamp) == sizeof(int64_t), "TimeStamp should be same size as int64_t");



/**
 * 将时间戳转换成字符串形式
 * 如果 microSecondsSinceEpoch_ 的值为 1623252883123456，则按照上述函数的处理方式，
 * 得到的字符串就是 "2021-06-09 15:08:03.123456"，其中秒数是 1623252883，微秒数是 123456。
*/
string TimeStamp::toString() const {
    LOG_INFO << "TimeStamp::toString()" ;

    char buf[32] = {0};

    int64_t seconds = microSecondsSinceEpoch_ / KMicroSencondsPerSecond;
    int64_t microseconds = microSecondsSinceEpoch_ % KMicroSencondsPerSecond;
    // %06" PRId64 ""表示输出6位数字的int64_t类型的整数并补零。
    snprintf(buf, sizeof(buf), "%",PRId64 ".%06" PRId64 "", seconds, microseconds);

    return buf;
}

//  toFormattedString 还包括了可选的是否显示微秒
string TimeStamp::toFormattedString(bool showMicroseconds) const {
    LOG_INFO << "TimeStamp::toFormattedString()";

    char buf[64] = {0};

}

// Get time of now. 返回当前时间戳。
TimeStamp TimeStamp::now(){
    LOG_INFO << "now()" ;
    
}