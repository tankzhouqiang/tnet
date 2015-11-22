#include <tnet/rpc/ChannelManager.h>
#include <tnet/network/DefaultPacketStream.h>
#include <tnet/network/TcpConnection.h>

using namespace std;
TNET_USE_NAMESPACE(network);
TNET_BEGIN_NAMESPACE(rpc);

ChannelManager::ChannelManager() { 
}

ChannelManager::~ChannelManager() { 
}


TnetRPCChannel* ChannelManager::openChannel(const string& spec, 
        int64_t timeout) 
{
    DefaultPacketStream packetStream;
    TcpConnection *connection = _transport.connect(spec, 
            &packetStream, timeout);
    TnetRPCChannel *channel = new TnetRPCChannel(connection);
    _channelVec.push_back(channel);
    return channel;
}

TNET_END_NAMESPACE(rpc);

