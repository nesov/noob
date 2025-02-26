#pragma once

#include <string>

#include "ssapi/INetworkService.h"
#include "ssapi/SocketBase.h"
#include "ssapi/Message.h"


class TcpSocketClient : public INetworkService { 
public:
    TcpSocketClient(std::string host, int port);
    ~TcpSocketClient();

    bool start() override;
    void stop() override;

    bool sendMessage(const Message &message) override;
    bool sendMessage(int socket, const Message &message) override;
    
    Message receiveMessage() override ;
    Message receiveMessage(int socket) override;

    bool isConnected() override; 
    int Accept() override;
private:
    SocketBase m_network;
    std::string m_host;
    int m_port;
};
