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
        if (memcmp(args, defaultPacket->getBody(), bodyLen) == 0) {
            LOG(ERROR) << "packet echo is not equal origin" << endl;
        }
        string echoString((char*)defaultPacket->getBody(), 
                          bodyLen);
        cout << echoString << endl;
    }
private:
};

int main(int argc, char** argv) {
//    google::InitGoogleLogging(argv[0]);
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
    uint32_t count = 100000;
    string str[count];
    for (uint32_t i = 0; i < count; i++) {
        str[i] = StringUtil::toString(i);
        DefaultPacket *packet = new DefaultPacket();
        packet->setBodyLen(str[i].length());
        packet->setBody((void*)str[i].data());
        // connection->postPacket(packet, &packetHandler, 
        //                        (void*)&str[i]);
    }
    transport.wait();
}

TNET_TYPEDEF_PTR(EchoPacketHandler);

#endif //TNET_ECHOCLIENT_H
