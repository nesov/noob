#include <unistd.h>
#include <arpa/inet.h>

#include <cstring>
#include <algorithm> 
#include <iostream>

#include "ssapi/TcpServer.h"

TcpServer::TcpServer(int port) : m_port(port), m_running(false) {
    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_serverSocket == -1) {
        std::cerr << "Failed to create socket\n";
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(m_port);

    if (bind(m_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Bind failed\n";
    }

    if (listen(m_serverSocket, 5) < 0) {
        std::cerr << "Listen failed\n";
    }
}

TcpServer::~TcpServer() {
    stop();
}

void TcpServer::start() {
    m_running = true;
    m_future = std::async(std::launch::async, &TcpServer::acceptClients, this);
}

void TcpServer::stop() {
    m_running = false;
    close(m_serverSocket);
    for (int client : m_clients) {
        close(client);
    }
}

void TcpServer::acceptClients() {
    sockaddr_in clientAddr{};
    socklen_t addrLen = sizeof(clientAddr);
    while (m_running) {
        int clientSocket = accept(m_serverSocket, (struct sockaddr* )&clientAddr, &addrLen);
        if (clientSocket < 0) {
            std::cerr << "Client accept failed\n";
            continue;
        }

        std::lock_guard<std::mutex> lock(m_mutex);
        m_clients.push_back(clientSocket);

        std::future<void> fut = std::async(std::launch::async, &TcpServer::handleClient, this, clientSocket);
    }
}

void TcpServer::handleClient(int clientSocket) {
    char buffer[1024] = {0};

    while (recv(clientSocket, buffer, sizeof(buffer), 0) > 0) {
        std::cout << "Received: " << buffer << std::endl;
        broadcastMessage(buffer);
    }

    close(clientSocket);
    std::lock_guard<std::mutex> lock(m_mutex);
    m_clients.erase(std::remove(m_clients.begin(), m_clients.end(), clientSocket), m_clients.end());
}

void TcpServer::broadcastMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (int client : m_clients) {
        send(client, message.c_str(), message.size(), 0);
    }
}
