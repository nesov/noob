#pragma once

#include "ssapi/Message.h"
#include "ssapi/INetworkService.h"
#include "ssapi/SocketBase.h"


class TcpSocketServer : public INetworkService  {
public:
    TcpSocketServer(int port);
    ~TcpSocketServer();

    bool start() override;
    void stop() override;

    bool sendMessage(const Message &message) override;
    bool sendMessage(int socket, const Message &message) override;

    Message receiveMessage(int socket) override;
    Message receiveMessage() override;

    bool isConnected() override;

    int Accept() override;

private:
    SocketBase m_network;
    int m_port;
};
