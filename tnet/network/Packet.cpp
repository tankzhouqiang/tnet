#include <tnet/network/Packet.h>

TNET_USE_NAMESPACE(util);
TNET_BEGIN_NAMESPACE(network);

Packet::Packet() 
    : _sendTime(TimeUtility::currentTime())
{ 
}

Packet::~Packet() { 
}

TNET_END_NAMESPACE(network);

