#include <tnet/rpc/TnetRPCChannel.h>

TNET_USE_NAMESPACE(network);
TNET_BEGIN_NAMESPACE(rpc);

TnetRPCChannel::TnetRPCChannel(TcpConnection *connection) :
    _connection(connection)
{
}

TnetRPCChannel::~TnetRPCChannel() {
    if (_connection) {
        delete _connection;
    }
}

TNET_END_NAMESPACE(rpc);

