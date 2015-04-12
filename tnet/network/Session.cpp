#include <tnet/network/Session.h>

TNET_BEGIN_NAMESPACE(network);

Session::Session(IPacketHandler *handler, void *args) 
    :_handler(handler)
    ,_args(args)
{ 
}

Session::~Session() { 
}

TNET_END_NAMESPACE(network);

