#ifndef TNET_TRANSPORT_H
#define TNET_TRANSPORT_H

#include <tnet/common/Common.h>
#include <tnet/network/ServerAdapter.h>
#include <tnet/network/ClientAdapter.h>
#include <tnet/network/EpollEvent.h>
#include <tnet/network/TcpAcceptor.h>
#include <tnet/network/TcpConnection.h>
#include <tnet/network/PacketStream.h>
#include <tnet/util/Thread.h>
#include <tnet/util/Lock.h>

TNET_BEGIN_NAMESPACE(network);

class Transport
{
public:
    static const std::string IP_PORT_SEPARATOR;
    static const uint32_t DEFAULT_THREAD_COUNT = 16;
public:
    Transport();
    ~Transport();
private:
    Transport(const Transport &);
    Transport& operator=(const Transport &);
public:
    bool init(const std::string& spec, PacketStream *packetStream, 
              ServerAdapter *adapter);
    //server interface
    void setThreadCount(uint32_t threadCount);
    //spec format IP:PORT
    bool listen(const std::string& spec, ServerAdapter *adapter);

    //start io thread and one timeout checkthread.
    bool start();

    //client interface
    //spec format IP:PORT
    bool connect(const std::string& spec, PacketStream *packetStream);

    void stop();
private:
    bool ioLoop();
public:
    //public for test
    bool parseAddress(const std::string& spec, std::string& ip, int& port);
private:
    std::vector<IOComponent*> _ioComponentVec;
    util::ThreadMutex _ioComponentVecLock;
    EpollEvent *_epollEvent;
    util::ThreadPtr _ioThreadPtr;
    util::ThreadPtr _checkTimeoutThreadPtr;
    bool _start;
};

TNET_TYPEDEF_PTR(Transport);

TNET_END_NAMESPACE(network);

#endif //TNET_TRANSPORT_H
