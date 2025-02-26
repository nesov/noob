
#pragma once

#include "ssapi/INetworkService.h"
#include "ssapi/TcpSocketClient.h"
#include "ssapi/TcpSocketServer.h"

class NetworkServiceFactory {
 public:
    NetworkServiceFactory() = default;
    ~NetworkServiceFactory() = default;
    INetworkService* createNetworkService(bool isClient , std::string host, int port);
};
