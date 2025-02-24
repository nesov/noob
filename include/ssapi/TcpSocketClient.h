#pragma once

#include "ssapi/INetworkService.h"
#include "ssapi/SocketBase.h"
#include "ssapi/Message.h"

#include <string>


class TcpSocketClient{ 
public:
    TcpSocketClient(std::string host, int port);
    ~TcpSocketClient();

    void start()  ;
    void stop()  ;

    // bool sendMessage(Message &message) ;
    // Message receiveMessage()  ;
   
private:
    SocketBase m_network;
    std::string m_host;
    int m_port;
};
