#include <tnet/network/SessionPool.h>
#include <tnet/network/TimeoutPacket.h>

using namespace std;
TNET_USE_NAMESPACE(util);

TNET_BEGIN_NAMESPACE(network);

SessionPool::SessionPool() 
    : _sessionId(0) { 
}

SessionPool::~SessionPool() { 
}

uint32_t SessionPool::allocateSession(IPacketHandler *handler, 
                                      void *args, Packet *packet, 
                                      int64_t timeout) 
{
    int64_t sendTime = packet->getSendTime();
    Session *session = new Session(handler, args, sendTime, timeout);
    ScopedLock lock(_sessionMutex);
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

void SessionPool::checkTimeout() {
    list<Session*> timeoutList;
    {
        ScopedLock lock(_sessionMutex);
        for (std::map<uint32_t, Session*>::iterator it = 
                 _sessionPool.begin(); it != _sessionPool.end();)
        {
            Session *session = it->second;
            uint32_t sessionId = it->first;
            assert(session);
            if (session->isTimeout()) {
                LOG(INFO) << "session " << sessionId 
                          << " is timeout" << endl;
                timeoutList.push_back(session);
                _sessionPool.erase(it++);
            } else {
                ++it;
            }
        }
    }
    for (list<Session*>::iterator it = timeoutList.begin(); 
         it != timeoutList.end(); ++it) 
    {
        Session *session = (*it);
        assert(session);
        TimeoutPacket timeoutPacket;
        IPacketHandler *handler = session->_handler;
        handler->handlePacket(&timeoutPacket, session->_args);
        delete session;
    }
}

Session* SessionPool::testSession(uint32_t sessionId) {
    ScopedLock lock(_sessionMutex);
    std::map<uint32_t, Session*>::iterator it = 
        _sessionPool.find(sessionId);
    if (it == _sessionPool.end()) {
        return NULL;
    }
    Session *session = it->second;
    return session;
}

TNET_END_NAMESPACE(network);

