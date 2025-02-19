
#include <unistd.h>
#include <arpa/inet.h>

#include <iostream>

#include "ssapi/TcpClient.h"
#include "ssapi/Consts.h"
#include "ssapi/Message.h"

TcpClient::TcpClient(const std::string& serverIp, int port) {
    connection.clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connection.clientSocket == -1) {
        std::cerr << "Failed to create socket\n";
    }

    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, serverIp.c_str(), &m_serverAddr.sin_addr);
}

TcpClient::~TcpClient() {
    disconnect();
}

bool TcpClient::connectToServer() {
    if (connect(connection.clientSocket, (struct sockaddr*)&m_serverAddr, sizeof(m_serverAddr)) == 0) {
        return true;
    }
    std::cerr << "Connection to server failed\n";
    return false;
}

// void TcpClient::sendMessage(const Message& message) {
//     std::lock_guard<std::mutex> lock(m_mutex);
//     size_t messageSize = sizeof(message);
//     char buffer[kBufferSize] = {0};
//     buffer = static_cast<char*>(message);
//     send(connection.clientSocket, buffer, messageSize, 0);
// }

// void TcpClient::sendMessage(const Message& message) {
//     std::lock_guard<std::mutex> lock(m_mutex);
//     std::string buffer = message.toBuffer();
//     uint32_t messageSize = buffer.size();
//     send(connection.clientSocket, &messageSize, sizeof(messageSize), 0);
//     send(connection.clientSocket, buffer.c_str(), buffer.size(), 0);
// }

void TcpClient::sendMessage(const Message& message) {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::string buffer = message.toBuffer();
    uint32_t messageSize = buffer.size();
    send(connection.clientSocket, &messageSize, sizeof(messageSize), 0);
    send(connection.clientSocket, buffer.c_str(), buffer.size(), 0);
}



// Message TcpClient::receiveMessage() {
//     std::lock_guard<std::mutex> lock(m_mutex);
//     char buffer[kBufferSize] = {0};
//     recv(connection.clientSocket, buffer, sizeof(buffer), 0);
//     Message message {buffer};
//     return message;
// }
// Message TcpClient::receiveMessage() {
//     uint32_t messageSize;
//     recv(connection.clientSocket, &messageSize, sizeof(messageSize), 0);
//     std::string buffer(messageSize, '\0');
//     recv(connection.clientSocket, buffer.data(), messageSize, 0);
//     Message message;
//     message.fromBuffer(buffer);
//     return message;
// }

Message TcpClient::receiveMessage() {
    uint32_t messageSize;
    recv(connection.clientSocket, &messageSize, sizeof(messageSize), 0);
    std::string buffer(messageSize, '\0');
    recv(connection.clientSocket, buffer.data(), messageSize, 0);
    Message message;
    message.fromBuffer(buffer);
    return message;
    // return Message::fromBuffer(buffer);
}



void TcpClient::disconnect() {
    close(connection.clientSocket);
}
