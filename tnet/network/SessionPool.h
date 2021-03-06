#ifndef TNET_SESSIONPOOL_H
#define TNET_SESSIONPOOL_H

#include <tnet/common/Common.h>
#include <tnet/network/Session.h>
#include <tnet/util/Lock.h>

TNET_BEGIN_NAMESPACE(network);

class SessionPool
{
public:
    SessionPool();
    ~SessionPool();
private:
    SessionPool(const SessionPool &);
    SessionPool& operator=(const SessionPool &);
public:
    uint32_t allocateSession(IPacketHandler *handler, void *args,
                             Packet *packet, int64_t timeout);
    Session* getSession(uint32_t sessionId);
    void checkTimeout();
    uint32_t getSessionCount() const {
      return _sessionCount;
    }
public:
//for test;
    Session* testSession(uint32_t sessionId);
private:
    uint32_t _sessionId;
    uint32_t _sessionCount;
    std::map<uint32_t, Session*> _sessionPool;
    util::ThreadMutex _sessionMutex;
};

TNET_TYPEDEF_PTR(SessionPool);

TNET_END_NAMESPACE(network);

#endif //TNET_SESSIONPOOL_H
