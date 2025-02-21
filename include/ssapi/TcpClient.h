#pragma once

#include <netinet/in.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <string>
#include <mutex>
#include <iostream>

#include "ssapi/INetworkService.h"
#include "ssapi/Message.h"
#include "ssapi/Connection.h"

namespace ssapi {

    class TcpClient : public INetworkService {
    public:
        TcpClient(const std::string &ip, int port);
        bool start() override;
        void stop() override;
        bool sendMessage(Message &message) override;
        Message receiveMessage() override;

    private:
        std::string m_serverIp;
        int m_serverPort;
        int m_socketFd;
    };

} // namespace ssapi


