#include <tnet/network/Packet.h>
#include <tnet/util/TimeUtility.h>

TNET_USE_NAMESPACE(util);
TNET_BEGIN_NAMESPACE(network);

Packet::Packet() 
    : _sendTime(TimeUtility::currentTime())
    , _timeout(DEFAULT_TIMEOUT)
{ 
}

Packet::~Packet() { 
}

TNET_END_NAMESPACE(network);

