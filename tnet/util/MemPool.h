#ifndef TNET_MEMPOOL_H
#define TNET_MEMPOOL_H

#include <tnet/common/Common.h>

TNET_BEGIN_NAMESPACE(util);

class MemPool
{
public:
    MemPool();
    ~MemPool();
private:
    MemPool(const MemPool &);
    MemPool& operator=(const MemPool &);
public:

private:
};

TNET_TYPEDEF_PTR(MemPool);

TNET_END_NAMESPACE(util);

#endif //TNET_MEMPOOL_H
