#include <tnet/network/SessionPool.h>

using namespace std;
TNET_USE_NAMESPACE(util);

TNET_BEGIN_NAMESPACE(network);

SessionPool::SessionPool() 
    : _sessionId(0) { 
}

SessionPool::~SessionPool() { 
}

uint32_t SessionPool::allocateSession(IPacketHandler *handler, 
                                      void *args) 
{
    ScopedLock lock(_sessionMutex);
    Session *session = new Session(handler, args);
    _sessionPool[_sessionId] = session;
    return _sessionId++;
}

Session* SessionPool::getSession(uint32_t sessionId) {
    ScopedLock lock(_sessionMutex);
    std::map<uint32_t, Session*>::iterator it = 
        _sessionPool.find(sessionId);
    if (it == _sessionPool.end()) {
        LOG(ERROR) << "session is not existed" << endl;
        return NULL;
    }
    //session is delete in getSession.
    Session *session = it->second;
    _sessionPool.erase(it);
    return session;
}

TNET_END_NAMESPACE(network);

