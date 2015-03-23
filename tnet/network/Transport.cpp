#include <tnet/network/Transport.h>
#include <tnet/util/StringUtil>

TNET_USE_NAMESPACE(util);

TNET_BEGIN_NAMESPACE(network);

static const string Transport::IP_PORT_SEPARATOR = ":";

Transport::Transport() 
    : _threadCount(DEFAULT_THREAD_COUNT)
    , _serverAdapter(NULL)
    , _clientAdapter(NULL)
{ 
}

Transport::~Transport() { 
}

void Transport::setThreadCount(uint32_t threadCount) {
    _threadCount = threadCount;
}



bool Transport::listen(const string& spec, ServerAdapter *adapter) {
    vector<string> specVec = StringUtil::split(spec, IP_PORT_SEPARATOR);
    if (specVec.size() != 2) {
        LOG(ERROR, "ip:port format error, spec:[%s]", spec);
        return false;
    }
    string ip = specVec[0];
    string port = specVec[1];
    
}

bool Transport::startServer() {
}


bool Transport::connect(const string& spec, ClientAdapter *adapter, 
                        void *args)
{
}

bool Transport::startClient() {
}

void Transport::stop() {
}

TNET_END_NAMESPACE(network);

