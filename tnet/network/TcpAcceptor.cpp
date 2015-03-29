#include <tnet/network/TcpAcceptor.h>
#include <tnet/util/StringUtil.h>
using namespace std;
TNET_BEGIN_NAMESPACE(network);

const string TcpAcceptor::IP_PORT_SEPARATOR = ":";

TcpAcceptor::TcpAcceptor() 
    : _serverAdapter(NULL)
{
}

TcpAcceptor::~TcpAcceptor() {
    if (_serverAdapter) {
        delete _serverAdapter;
        _serverAdapter = NULL;
    }
}

bool TcpAcceptor::parseAddress(const string& spec, string& ip, int& port) {
    vector<string> specVec = util::StringUtil::split(spec, IP_PORT_SEPARATOR);
    if (specVec.size() != 2) {
        LOG(ERROR) <<  "ip:port format error, spec:[" << spec << "]";
        return false;
    }
    ip = specVec[0];
    const string& portStr = specVec[1];
    port = atoi(portStr.data());
    return true;
}

bool TcpAcceptor::init(const string& spec, ServerAdapter *adapter) {
    string ip;
    int port;
    if (!parseAddress(spec, ip, port)) {
        return false;
    }
    _socket = new ServerSocket(ip, port);
    if (!_socket->init()) {
        delete _socket;
        return false;
    }
    _socket->setIOComponent(this);
    _serverAdapter = adapter;
    
    return true;
}


TNET_END_NAMESPACE(network);

