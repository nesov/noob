

#include "ssapi/NetworkServiceFactory.h"


INetworkService* NetworkServiceFactory::createNetworkService(bool isClient, std::string host, int port) {

    switch (static_cast<int>(isClient)) {
    case  0:
        return new TcpSocketServer(port);
    
    case  1:
        return new TcpSocketClient(host,port);
    
    default:
        std::cerr <<"Unsupported mode is set\n";
        return nullptr;
    }
}