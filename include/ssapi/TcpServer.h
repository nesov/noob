#pragma once

#include <vector>
#include <mutex>
#include <future>
#include <netinet/in.h> 

#include "ssapi/Message.h"
#include "ssapi/INetworkService.h"

namespace ssapi {
    class TcpServer : public INetworkService {
    public:
        explicit TcpServer(int port);
        bool start() override;
        void stop() override;

        bool sendMessage(const Message &message) override;
        Message receiveMessage() override;

    private:
        int m_serverFd;
        int m_port;
        std::mutex m_clientsMutex;
        std::vector<int> m_clients;
    };
} //namespace ssapi
