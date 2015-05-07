#include <tnet/util/TimeUtility.h>

TNET_BEGIN_NAMESPACE(util);

TimeUtility::TimeUtility() { 
}

TimeUtility::~TimeUtility() { 
}

int64_t TimeUtility::currentTime() {
    struct timeval tval;
    gettimeofday(&tval, NULL);
    return (tval.tv_sec * 1000000LL + tval.tv_usec);
}

TNET_END_NAMESPACE(util);

