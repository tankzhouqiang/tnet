#ifndef TNET_TIMEUTILITY_H
#define TNET_TIMEUTILITY_H

#include <tnet/common/Common.h>
#include <sys/time.h>

TNET_BEGIN_NAMESPACE(util);

class TimeUtility
{
public:
    TimeUtility();
    ~TimeUtility();
private:
    TimeUtility(const TimeUtility &);
    TimeUtility& operator=(const TimeUtility &);
public:
    static int64_t currentTime();
private:
};

TNET_TYPEDEF_PTR(TimeUtility);

TNET_END_NAMESPACE(util);

#endif //TNET_TIMEUTILITY_H
