#include <tnet/network/IOEvent.h>

TNET_BEGIN_NAMESPACE(network);

IOEvent::IOEvent() 
    : _ioc(NULL)
    , _readOccurred(false)
    , _writeOccurred(false)
    , _errorOccurred(false)
{ 
}

IOEvent::~IOEvent() { 
}

TNET_END_NAMESPACE(network);

