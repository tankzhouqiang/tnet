#include <tnet/rpc/SyncRPCClosure.h>

TNET_BEGIN_NAMESPACE(rpc);

SyncRPCClosure::SyncRPCClosure() 
    : _needWait(true)
{ 
}

SyncRPCClosure::~SyncRPCClosure() { 
}

TNET_END_NAMESPACE(rpc);

