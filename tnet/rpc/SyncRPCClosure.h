#ifndef TNET_SYNCRPCCLOSURE_H
#define TNET_SYNCRPCCLOSURE_H

#include <tnet/common/Common.h>
#include <tnet/util/Lock.h>

TNET_BEGIN_NAMESPACE(rpc);

class SyncRPCClosure : public google::protobuf::Closure
{
public:
    SyncRPCClosure();
    ~SyncRPCClosure();
private:
    SyncRPCClosure(const SyncRPCClosure &);
    SyncRPCClosure& operator=(const SyncRPCClosure &);
public:
    void waitReply() {
        util::ScopedLock lock(_cond);
        while (_needWait) {
            _cond.wait();
        }
    }
    virtual void Run() {
        util::ScopedLock lock(_cond);
        _needWait = false;
        _cond.signal();
    }
private:
    bool _needWait;
    util::ThreadCond _cond;
};

TNET_TYPEDEF_PTR(SyncRPCClosure);

TNET_END_NAMESPACE(rpc);

#endif //TNET_SYNCRPCCLOSURE_H
