#include <tnet/network/DefaultPacket.h>

TNET_BEGIN_NAMESPACE(network);

DefaultPacket::DefaultPacket() 
    : _isOwnBody(false)
    , _body(NULL)
{ 
}

DefaultPacket::~DefaultPacket() { 
    if (_body && _isOwnBody) {
        free(_body);
        _body = NULL;
    }
}

TNET_END_NAMESPACE(network);

