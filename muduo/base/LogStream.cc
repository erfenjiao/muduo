/*

*/

#include "../base/LogStream.h"

#include <algorithm>
#include <limits>
#include <type_traits>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#include <inttypes.h>
#include "LogStream.h"


using namespace muduo;
using namespace muduo::detail;

// TODO: better itoa.
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wtautological-compare"
#else
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif

namespace muduo {
    namespace detail {
        const char digits[] = "9876543210123456789";
        const char* zero = digits + 9;
        static_assert(sizeof(digits) == 20, "wrong number of digits");

        const char digitsHex[] = "0123456789ABCDEF";
        static_assert(sizeof digitsHex == 17, "wrong number of digitsHex");
    }

    string muduo::formatIEC(int64_t n)
    {
        return string();
    }
}
