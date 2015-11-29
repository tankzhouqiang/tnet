#ifndef TNET_TNETRPCCONTROLLER_H
#define TNET_TNETRPCCONTROLLER_H

#include <tnet/common/Common.h>

TNET_BEGIN_NAMESPACE(rpc);

class TnetRpcController : public google::protobuf::RpcController
{
public:
    TnetRpcController();
    ~TnetRpcController();
private:
    TnetRpcController(const TnetRpcController &);
    TnetRpcController& operator=(const TnetRpcController &);
public:
    virtual bool Failed() const 
    {
        return _failed;
    }

    virtual void SetFailed(const std::string& reason) {
        _failed = true;
        _reason = reason;
    }

    virtual void Reset() {};
    
    virtual std::string ErrorText() {
        return _reason;
    }

    virtual void StartCancel() {}
    virtual bool IsCanceled() {}
    virtual void NotifyOnCancel(google::protobuf::Closure* callback) {}
private:
    bool _failed;
    std::string _reason;
};

TNET_TYPEDEF_PTR(TnetRpcController);

TNET_END_NAMESPACE(rpc);

#endif //TNET_TNETRPCCONTROLLER_H
