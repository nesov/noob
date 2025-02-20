
#include "ssapi/TcpClient.h"

namespace ssapi {

    TcpClient::TcpClient(const std::string& ip, int port) 
                    : m_serverIp(ip), m_serverPort(port), m_socketFd(-1) {}

    bool TcpClient::start() {
        m_socketFd = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socketFd < 0)
            return false;
        sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(m_serverPort);
        inet_pton(AF_INET, m_serverIp.c_str(), &serverAddr.sin_addr);

        return connect(m_socketFd, (sockaddr *)&serverAddr, sizeof(serverAddr)) == 0;
    }

    void TcpClient::stop() {
        if (m_socketFd >= 0)
            close(m_socketFd);
    }

    bool TcpClient::sendMessage(const Message &message) {
        std::vector<char> buffer = message.toBuffer();
        size_t totalSent = 0;
        size_t toSend = buffer.size();

        while (totalSent < toSend){
            ssize_t sent = ::send(m_socketFd, buffer.data() + totalSent, toSend - totalSent, 0);
            if (sent <= 0)
                return false;
            totalSent += sent;
        }
        return true;
    }

    Message TcpClient::receiveMessage() {
        uint32_t messageSize = 0;
        ssize_t received = ::recv(m_socketFd, &messageSize, sizeof(messageSize), MSG_WAITALL);
        if (received != sizeof(messageSize)) {
            throw std::runtime_error("Connection closed or error on receive");
        }

        messageSize = ntohl(messageSize);
        std::vector<char> buffer(messageSize);
        size_t totalReceived = 0;

        while (totalReceived < messageSize) {
            ssize_t bytesRead = ::recv(m_socketFd, buffer.data() + totalReceived, messageSize - totalReceived, 0);
            if (bytesRead <= 0) {
                throw std::runtime_error("Connection closed or error on receive");
            }
            totalReceived += bytesRead;
        }
        return Message::fromBuffer(buffer);
    }
    
} //namespace ssapi