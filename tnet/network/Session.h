#ifndef TNET_SESSION_H
#define TNET_SESSION_H

#include <tnet/common/Common.h>
#include <tnet/network/IPacketHandler.h>
#include <tnet/util/TimeUtility.h>

TNET_BEGIN_NAMESPACE(network);

class Session
{
public:
    Session(IPacketHandler *handler, void *args,
            int64_t sendtime, int64_t timeout);
    ~Session();
private:
    Session(const Session &);
    Session& operator=(const Session &);
public:
    bool isTimeout() {
        if (_timeout == -1) {
            return false;
        }
        int64_t currentTime = util::TimeUtility::currentTime();
        return  currentTime - _sendTime > _timeout;
    }
public:
    IPacketHandler *_handler;
    void *_args;
    int64_t _sendTime;
    int64_t _timeout;
};

TNET_TYPEDEF_PTR(Session);

TNET_END_NAMESPACE(network);

#endif //TNET_SESSION_H
