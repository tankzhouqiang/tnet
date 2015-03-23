#ifndef TNET_CLIENTADAPTER_H
#define TNET_CLIENTADAPTER_H

#include <tnet/common/Common.h>

TNET_BEGIN_NAMESPACE(network);

class ClientAdapter
{
public:
    ClientAdapter();
    ~ClientAdapter();
private:
    ClientAdapter(const ClientAdapter &);
    ClientAdapter& operator=(const ClientAdapter &);
public:

private:
};

TNET_TYPEDEF_PTR(ClientAdapter);

TNET_END_NAMESPACE(network);

#endif //TNET_CLIENTADAPTER_H
