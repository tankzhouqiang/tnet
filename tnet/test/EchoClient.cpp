#ifndef TNET_ECHOCLIENT_H
#define TNET_ECHOCLIENT_H

#include <tnet/common/Common.h>
#include <tnet/network/IPacketHandler.h>
#include <tnet/network/DefaultPacket.h>
#include <tnet/network/DefaultPacketStream.h>
#include <tnet/network/Transport.h>
#include <tnet/network/TcpConnection.h>
#include <tnet/util/StringUtil.h>

TNET_USE_NAMESPACE(network);
TNET_USE_NAMESPACE(util);
using namespace std;

class EchoPacketHandler : public IPacketHandler
{
public:
    EchoPacketHandler() {}
    ~EchoPacketHandler() {}
private:
    EchoPacketHandler(const EchoPacketHandler &);
    EchoPacketHandler& operator=(const EchoPacketHandler &);
public:
    /*override*/ virtual void handlePacket(Packet *packet, 
            void *args) 
    {
        assert(packet);
        DefaultPacket *defaultPacket = 
            dynamic_cast<DefaultPacket*>(packet);
        assert(defaultPacket);
        uint32_t bodyLen = defaultPacket->getBodyLen();
        string echoString((char*)defaultPacket->getBody(), 
                          bodyLen);
        cout << "client receive " << echoString << endl;
        if (memcmp(args, defaultPacket->getBody(), bodyLen) != 0) {
            string argsStr((char*)args, bodyLen);
            LOG(ERROR) << "packet echo " <<  
                echoString << "is not equal origin" << argsStr << "end" << endl;
            assert(false);
        }
    }
private:
};

int main(int argc, char** argv) {
   google::InitGoogleLogging(argv[0]);
   google::SetStderrLogging(google::INFO);
   google::SetLogDestination(google::INFO, "INFO_");
   google::SetLogDestination(google::WARNING, "WARNING_");
   google::SetLogDestination(google::ERROR, "ERROR_");
    if (argc != 2) {
        LOG(ERROR) << "./echo_client server_ip:server_port";
        exit(-1);
    }
    string spec = argv[1];
    DefaultPacketStream packetStream;
    EchoPacketHandler packetHandler;
    Transport transport;
    if (!transport.start()) {
        LOG(ERROR) << "transport start error";
        exit(-3);
    }
    TcpConnection *connection = transport.connect(spec, &packetStream);
    assert(connection);
    uint32_t count = 10;
    string str[count];
    for (uint32_t i = 0; i < count; i++) {
        str[i] = StringUtil::toString(i);
        DefaultPacket *packet = new DefaultPacket();
        packet->setBodyLen(str[i].length());
        packet->setBody((void*)str[i].data());
        connection->postPacket(packet, &packetHandler, 
                               (void*)str[i].data());
        sleep(1);
    }
    transport.wait();
}

TNET_TYPEDEF_PTR(EchoPacketHandler);

#endif //TNET_ECHOCLIENT_H
