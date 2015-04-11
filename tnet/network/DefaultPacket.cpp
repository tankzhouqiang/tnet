#include <tnet/network/DefaultPacket.h>

TNET_BEGIN_NAMESPACE(network);

DefaultPacket::DefaultPacket() 
    : _body(NULL)
{ 
}

DefaultPacket::~DefaultPacket() { 
}

TNET_END_NAMESPACE(network);

