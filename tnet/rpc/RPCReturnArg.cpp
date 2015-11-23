#include <tnet/rpc/RPCReturnArg.h>

TNET_BEGIN_NAMESPACE(rpc);

RPCReturnArg::RPCReturnArg(
        google::protobuf::RpcController *controller,
        google::protobuf::Message *response,
        google::protobuf::Closure *done)
    : _controller(controller)
    , _response(response)
    , _done(done)
{
}

RPCReturnArg::~RPCReturnArg() { 
    
}

TNET_END_NAMESPACE(rpc);

