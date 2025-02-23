#pragma once

#include <vector>
#include <mutex>
#include <netinet/in.h> 

#include "ssapi/Message.h"
#include "ssapi/INetworkService.h"


    class TcpServer : public INetworkService {
    public:
        explicit TcpServer(int port);
        ~TcpServer();
        bool start() override;
        void stop() override;

        bool sendMessage(Message &message) override;
        Message receiveMessage() override;

    private:
        int m_serverFd;
        int m_port;
        std::mutex m_clientsMutex;
        std::vector<int> m_clients;
    };


