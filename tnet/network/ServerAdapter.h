#ifndef TNET_SERVERADAPTER_H
#define TNET_SERVERADAPTER_H

#include <tnet/common/Common.h>

TNET_BEGIN_NAMESPACE(network);

class ServerAdapter
{
public:
    ServerAdapter();
    ~ServerAdapter();
private:
    ServerAdapter(const ServerAdapter &);
    ServerAdapter& operator=(const ServerAdapter &);
public:

private:
};

TNET_TYPEDEF_PTR(ServerAdapter);

TNET_END_NAMESPACE(network);

#endif //TNET_SERVERADAPTER_H
