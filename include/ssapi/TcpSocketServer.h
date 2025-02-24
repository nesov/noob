#pragma once

#include "ssapi/Message.h"
#include "ssapi/INetworkService.h"
#include "ssapi/SocketBase.h"


class TcpSocketServer : public INetworkService  {
public:
    TcpSocketServer(int port);
    ~TcpSocketServer();

    void start() override;
    void stop() override;

    bool sendMessage(Message &message) override;
    Message receiveMessage() override;

    bool sendMessage(int socket, Message &message)override;
    Message receiveMessage(int socket)override;

private:
    SocketBase m_network;
    int m_port;
};
