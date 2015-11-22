#ifndef TNET_CHANNELMANAGER_H
#define TNET_CHANNELMANAGER_H

#include <tnet/common/Common.h>
#include <tnet/network/Transport.h>
#include <tnet/rpc/TnetRPCChannel.h>

TNET_BEGIN_NAMESPACE(rpc);

class ChannelManager
{
public:
    ChannelManager();
    ~ChannelManager();
private:
    ChannelManager(const ChannelManager &);
    ChannelManager& operator=(const ChannelManager &);
public:
    TnetRPCChannel* openChannel(const std::string& spec, 
                                int64_t timeout);
private:
    network::Transport _transport;
    std::vector<TnetRPCChannel*>  _channelVec;
};

TNET_TYPEDEF_PTR(ChannelManager);

TNET_END_NAMESPACE(rpc);

#endif //TNET_CHANNELMANAGER_H
