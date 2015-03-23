#ifndef TNET_TRANSPORT_H
#define TNET_TRANSPORT_H

#include <tnet/common/Common.h>
#include <tnet/network/ServerAdapter.h>

TNET_BEGIN_NAMESPACE(network);

class Transport
{
public:
    static const std::string IP_PORT_SEPARATOR;
    static const uint32_t DEFAULT_THREAD_COUNT = 16;
public:
    Transport();
    ~Transport();
public:
    //server interface
    void setThreadCount(uint32_t threadCount);
    //spec format IP:PORT
    bool listen(const string& spec, ServerAdapter *adapter);
    //start server multi io thread and one timeout checkthread.
    bool startServer();

    //client interface
    //spec format IP:PORT
    bool connect(const string& spec, ClientAdapter *adapter, void *args);

    //start server one io thread and one timeout checkthread.
    bool startClient();

    void stop();

private:
    string 
private:
    Transport(const Transport &);
    Transport& operator=(const Transport &);
public:
    uint32_t _threadCount;
    ServerAdapter *_serverAdapter;
    ClientAdapter *_clientAdapter;    
private:
};

TNET_TYPEDEF_PTR(Transport);

TNET_END_NAMESPACE(network);

#endif //TNET_TRANSPORT_H
