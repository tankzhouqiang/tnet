#include <tnet/network/IOComponent.h>

TNET_BEGIN_NAMESPACE(network);

IOComponent::IOComponent() 
    : _socket(NULL)
    , _closed(false)
{ 
}

IOComponent::~IOComponent() { 
    if (_socket) {
        delete _socket;
        _socket = NULL;
    }
}

TNET_END_NAMESPACE(network);

