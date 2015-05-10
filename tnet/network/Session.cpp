#include <tnet/network/Session.h>

TNET_BEGIN_NAMESPACE(network);

Session::Session(IPacketHandler *handler, void *args, 
                 int64_t sendtime, int64_t timeout) 
    : _handler(handler)
    , _args(args)
    , _sendTime(sendtime)
    , _timeout(timeout)
{ 
}

Session::~Session() { 
}

TNET_END_NAMESPACE(network);

