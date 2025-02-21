
#include "ssapi/TcpServer.h"
#include "ssapi/Message.h"
#include <unistd.h>

namespace ssapi {

    TcpServer::TcpServer(int port) : m_serverFd(-1), m_port(port) {}

    bool TcpServer::TcpServer::start() {
        m_serverFd = socket(AF_INET, SOCK_STREAM, 0);
        if (m_serverFd < 0) return false;

        sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(m_port);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(m_serverFd, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) return false;
        if (listen(m_serverFd, SOMAXCONN) < 0) return false;

        std::thread([this] {
                while (true) {
                    int clientFd = accept(m_serverFd, nullptr, nullptr);
                    if (clientFd >= 0) {
                        std::lock_guard<std::mutex> lock(m_clientsMutex);
                        m_clients.push_back(clientFd);
                    }
                } }).detach();
        return true;
    }

    void TcpServer::stop() {
        std::lock_guard<std::mutex> lock(m_clientsMutex);
        for (int client : m_clients) {
            close(client);
        }
        if (m_serverFd >= 0) { 
            close(m_serverFd);
        }
    }

    bool TcpServer::sendMessage(const Message &message) {
        std::lock_guard<std::mutex> lock(m_clientsMutex);
        for (int clientFd : m_clients) {
            std::vector<char> buffer = message.toBuffer();
            size_t totalSent = 0;
            size_t toSend = buffer.size();

            while (totalSent < toSend) {
                ssize_t sent = ::send(clientFd, buffer.data() + totalSent, toSend - totalSent, 0);
                if (sent <= 0)
                    return false;
                totalSent += sent;
            }
        }
        return true;
    }

    Message TcpServer::receiveMessage() {
        std::lock_guard<std::mutex> lock(m_clientsMutex);
        for (int clientFd : m_clients) {
            uint32_t messageSize = 0;
            ssize_t received = ::recv(clientFd, &messageSize, sizeof(messageSize), MSG_WAITALL);
            if (received != sizeof(messageSize)) {
                continue;
            }

            messageSize = ntohl(messageSize);
            std::vector<char> buffer(messageSize);
            size_t totalReceived = 0;

            while (totalReceived < messageSize) {
                ssize_t bytesRead = ::recv(clientFd, buffer.data() + totalReceived, messageSize - totalReceived, 0);
                if (bytesRead <= 0) {
                    continue;
                }
                totalReceived += bytesRead;
            }
            return Message::fromBuffer(buffer);
        }
        throw std::runtime_error("No clients connected or no message received");
        // return {"Error"};
    }
 
 }//namespace ssapi
