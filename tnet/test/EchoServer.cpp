#ifndef TNET_ECHOSERVER_H
#define TNET_ECHOSERVER_H

#include <tnet/common/Common.h>
#include <tnet/network/ServerAdapter.h>
#include <tnet/network/DefaultPacketStream.h>
#include <tnet/network/Transport.h>

TNET_USE_NAMESPACE(network);
using namespace std;

class EchoServerAdapter : public ServerAdapter
{
public:
    EchoServerAdapter() {}
    ~EchoServerAdapter() {}
private:
    EchoServerAdapter(const EchoServerAdapter &);
    EchoServerAdapter& operator=(const EchoServerAdapter &);
public:
    /*override*/ virtual void handlePacket(Packet *packet, 
            TcpConnection *connection) {
        assert(packet);
        assert(connection);
        cout << "server recive packet" << endl;
        connection->postPacket(packet);
    }
};

TNET_TYPEDEF_PTR(EchoServerAdapter);

int main(int argc, char** argv) {
//    google::InitGoogleLogging(argv[0]);
    if (argc != 2) {
        LOG(ERROR) << "./echo_server ip:port";
        exit(-1);
    }
    string spec = argv[1];
    DefaultPacketStream packetStream;
    EchoServerAdapter adapter;
    Transport transport;
    if (!transport.init(spec, &packetStream, &adapter)) {
        LOG(ERROR) << "transport init error";
        exit(-2);
    }
    if (!transport.start()) {
        LOG(ERROR) <<  "transport start error";
        exit(-3);
    }
    transport.wait();
}


#endif //TNET_ECHOSERVER_H
