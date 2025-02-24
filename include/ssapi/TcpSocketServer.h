#pragma once

#include "ssapi/Message.h"
#include "ssapi/INetworkService.h"
#include "ssapi/SocketBase.h"


class TcpSocketServer {
public:
    TcpSocketServer(int port);
    ~TcpSocketServer();

    void start()  ;
    void stop() ;

    // bool sendMessage(Message &message) ;
    // Message receiveMessage() ;

private:
    SocketBase m_network;
    int m_port;
};
