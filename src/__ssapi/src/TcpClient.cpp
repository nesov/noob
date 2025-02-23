
#include "ssapi/TcpClient.h"

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

    bool TcpClient::sendMessage(Message &message) {
        std::vector<char> buffer;
        message.serialize(buffer);
        size_t messageSize = buffer.size();
        ssize_t bytesSent = send(m_socketFd, &messageSize, sizeof(messageSize), 0);
        if (bytesSent < 0){
            std::cerr << "Error sending size" << std::endl;
            return false;
        }
        bytesSent = send(m_socketFd, buffer.data(), buffer.size(), 0);
        if (bytesSent < 0){
            std::cerr << "Error sending data" << std::endl;
            return false;
        }
        return true;
    }

    // Message TcpClient::receiveMessage() {
    //     size_t messageSize = 0;
    //     ssize_t bytesRead = recv(m_socketFd, &messageSize, sizeof(messageSize), 0);
    //     if (bytesRead < 0) {
    //         std::cerr << "Error receiving size" << std::endl;
    //         return nullptr;
    //     }
    //     std::vector<char> buffer(messageSize);
    //     bytesRead = recv(m_socketFd, buffer.data(), messageSize, 0);
    //     if (bytesRead < 0) {
    //         std::cerr << "Error receiving data" << std::endl;
    //         return nullptr;
    //     }
    //     // Message message = Message::deserialize(buffer);
    //     return {Message::deserialize(buffer)};
    // }

    Message TcpClient::receiveMessage(){
        size_t messageSize = 0;
        size_t bytesRead = recv(m_socketFd, &messageSize, sizeof(messageSize), 0);
        if (bytesRead < 0) {
            std::cerr << "Error receiving size" << std::endl;
            return Message();
        }
        std::vector<char> buffer(messageSize);
        bytesRead = recv(m_socketFd, buffer.data(), messageSize, 0);
        if (bytesRead < 0) {
            std::cerr << "Error receiving data" << std::endl;
            return Message();
        }
        // Message message = Message::deserialize(buffer);
        // std::cout<<__LINE__<<message;
        return Message::deserialize(buffer);
        // return message;
    }
