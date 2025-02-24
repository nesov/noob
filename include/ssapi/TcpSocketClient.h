#pragma once

#include "ssapi/INetworkService.h"
#include "ssapi/SocketBase.h"
#include "ssapi/Message.h"

#include <string>


class TcpSocketClient : public INetworkService { 
public:
    TcpSocketClient(std::string host, int port);
    ~TcpSocketClient();

    void start() override;
    void stop() override;

    bool sendMessage(Message &message) override;
    Message receiveMessage() override ;

    bool sendMessage(int socket, Message &message);

    Message receiveMessage(int socket);

private:
    SocketBase m_network;
    std::string m_host;
    int m_port;
};
