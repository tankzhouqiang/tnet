#ifndef TNET_ECHOCLIENT_H
#define TNET_ECHOCLIENT_H

#include <tnet/common/Common.h>
#include <tnet/network/IPacketHandler.h>
#include <tnet/network/DefaultPacket.h>
#include <tnet/network/DefaultPacketStream.h>
#include <tnet/network/Transport.h>
#include <tnet/network/TcpConnection.h>
#include <tnet/util/StringUtil.h>
#include <tnet/util/Thread.h>

TNET_USE_NAMESPACE(network);
TNET_USE_NAMESPACE(util);
using namespace std;

class EchoPacketHandler : public IPacketHandler
{
public:
    EchoPacketHandler() {}
    ~EchoPacketHandler() {}
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
	LOG(INFO) << "client receive " << echoString << endl;
        if (memcmp(args, defaultPacket->getBody(), bodyLen) != 0) {
            string argsStr((char*)args, bodyLen);
            LOG(ERROR) << "packet echo " <<  
                echoString << "is not equal origin" << argsStr << "end" << endl;
            assert(false);
        }
    }
private:
};

EchoPacketHandler packetHandler;

void runSendMsgThread(TcpConnection *connection, uint32_t msgCount, 
		      uint32_t msgLength, string str) 
{
    assert(connection);
    cout << "msgLength: " << str.length() << endl;
    for (uint32_t i = 0; i < msgCount; i++) {
        DefaultPacket *packet = new DefaultPacket();
        packet->setBodyLen(str.length());
        packet->setBody((void*)str.data());
        connection->postPacket(packet, &packetHandler, (void*)str.data());
    }
}


int main(int argc, char** argv) {
   google::InitGoogleLogging(argv[0]);
   google::SetStderrLogging(google::INFO);
   google::SetLogDestination(google::INFO, "INFO_");
   google::SetLogDestination(google::WARNING, "WARNING_");
   google::SetLogDestination(google::ERROR, "ERROR_");
    if (argc != 5) {
        LOG(ERROR) << "./echo_client server_ip:server_port thread_count msg_count msg_length";
        exit(-1);
    }
    string spec = argv[1];
    DefaultPacketStream packetStream;
    Transport transport;
    if (!transport.start()) {
        LOG(ERROR) << "transport start error";
        exit(-3);
    }
    
    uint32_t threadCount = 0;
    uint32_t msgCount = 0;
    uint32_t msgLength = 0;
    if (!StringUtil::strToUInt32(argv[2], threadCount)) {
        LOG(ERROR) << "thread count error: " << argv[2] << endl;
        return false;
    }
    if (!StringUtil::strToUInt32(argv[3], msgCount)) {
        LOG(ERROR) << "msg count error: " << argv[3] << endl;
        return false;
    }

    if (!StringUtil::strToUInt32(argv[4], msgLength)) {
        LOG(ERROR) << "msg length error: " << argv[4] << endl;
        return false;
    }

    string str(msgLength, 'a');

    ThreadPtr threadPtr[threadCount];
    for (uint32_t i = 0; i < threadCount; ++i) {
        TcpConnection *connection = transport.connect(spec, &packetStream, -1);
        assert(connection);
        threadPtr[i] = Thread::createThread(tr1::bind(&runSendMsgThread, 
						      connection, msgCount, msgLength, str));
        assert(threadPtr);
    }
    transport.wait();
}

TNET_TYPEDEF_PTR(EchoPacketHandler);

#endif //TNET_ECHOCLIENT_H
