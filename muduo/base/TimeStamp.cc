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
    snprintf(buf, sizeof(buf), "%" PRId64 ".%06" PRId64 "", seconds, microseconds);

    return buf;
}


/*
  将时间戳转化成格式化的字符串。
  函数的参数 showMicroseconds 控制是否显示微秒，如果为 true，则输出精确到微秒的时间；否则，只输出时分秒。
*/
string TimeStamp::toFormattedString(bool showMicroseconds) const {
    LOG_INFO << "TimeStamp::toFormattedString()";

    char buf[64] = {0};
    // 将毫秒级的时间戳 microSecondsSinceEpoch_ 转换成秒级的时间戳 seconds。
    time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / KMicroSencondsPerSecond);
    /*
      struct tm
      {
        int tm_sec;			 Seconds.	[0-60] (1 leap second) 
        int tm_min;			 Minutes.	[0-59] 
        int tm_hour;			 Hours.	[0-23] 
        int tm_mday;			 Day.		[1-31] 
        int tm_mon;			 Month.	[0-11] 
        int tm_year;			 Year	- 1900.
        int tm_wday;			 Day of week.	[0-6] 
        int tm_yday;			 Days in year.[0-365]	
        int tm_isdst;		 DST.		[-1/0/1]

      # ifdef	__USE_MISC
        long int tm_gmtoff;		 Seconds east of UTC.  
        const char *tm_zone;		Timezone abbreviation.  
      # else
        long int __tm_gmtoff;		 Seconds east of UTC.  
        const char *__tm_zone;	 Timezone abbreviation.  
      # endif
      };
    */
    struct tm tm_time;
    gmtime_r(&seconds, &tm_time);

    if(showMicroseconds) {
      int microseconds = static_cast<int>(microSecondsSinceEpoch_ % KMicroSencondsPerSecond);
      snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
               tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
               tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
               microseconds);
    }
    else
    {
      snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
              tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
              tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
    }
    return buf;

}

// Get time of now. 返回当前时间戳。
TimeStamp TimeStamp::now(){
    LOG_INFO << "now()" ;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t seconds = tv.tv_sec;
    return TimeStamp(seconds * KMicroSencondsPerSecond + tv.tv_usec);
    
}

/*

string Timestamp::toFormattedString(bool showMicroseconds) const
{
  char buf[64] = {0};
  time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
  struct tm tm_time;
  gmtime_r(&seconds, &tm_time);

  if (showMicroseconds)
  {
    int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
    snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
             tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
             tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
             microseconds);
  }
  else
  {
    snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
             tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
             tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
  }
  return buf;
}

Timestamp Timestamp::now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  int64_t seconds = tv.tv_sec;
  return Timestamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);
}
*/