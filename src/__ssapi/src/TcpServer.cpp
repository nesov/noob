
#include "ssapi/TcpServer.h"
#include "ssapi/Message.h"
#include <unistd.h>
#include <thread>


    TcpServer::TcpServer(int port) : m_serverFd(-1), m_port(port) {
        start();
    }

    TcpServer::~TcpServer() {
        stop();
    }

    bool TcpServer::TcpServer::start() {
        m_serverFd = socket(AF_INET, SOCK_STREAM, 0);
        if (m_serverFd < 0) 
            return false;

        sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(m_port);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(m_serverFd, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
            return false;

        if (listen(m_serverFd, SOMAXCONN) < 0) 
            return false;

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

    bool TcpServer::sendMessage(Message &message) {
        std::lock_guard<std::mutex> lock(m_clientsMutex);
        for (int clientFd : m_clients) {
            std::vector<char> buffer;
            message.serialize(buffer);
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
            return Message::deserialize(buffer);
        }
        throw std::runtime_error("No clients connected or no message received");
        // return {"Error"};
        // return nullptr
    }
 
//  }//namespace ssapi



// #include "ssapi/TcpServer.h"
// #include <iostream>
// #include <cstring>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <fcntl.h>

// namespace ssapi{


// TcpServer::TcpServer(int port, MessageHandler& handler)
//     : m_port(port), m_handler(handler), m_maxFd(0) {
//     m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
//     if (m_serverSocket < 0) {
//         return;
//     }

//     int opt = 1;
//     setsockopt(m_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

//     sockaddr_in serverAddr{};
//     serverAddr.sin_family = AF_INET;
//     serverAddr.sin_addr.s_addr = INADDR_ANY;
//     serverAddr.sin_port = htons(m_port);

//     if (bind(m_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
//         return;
//     }

//     if (listen(m_serverSocket, SOMAXCONN) < 0) {
//         return;
//     }

//     FD_ZERO(&m_masterSet);
//     FD_SET(m_serverSocket, &m_masterSet);
//     m_maxFd = m_serverSocket;
// }

// TcpServer::~TcpServer() {
//     stop();
//     close(m_serverSocket);
// }

// bool TcpServer::start() {
//     m_running = true;
//     m_workerThreads.emplace_back(std::async(std::launch::async, &TcpServer::acceptConnections, this));
//     m_workerThreads.emplace_back(std::async(std::launch::async, &TcpServer::processMessages, this));
//     return true;
// }

// void TcpServer::stop() {
//     m_running = false;
//     m_queueCV.notify_all();

//     for (auto& thread : m_workerThreads) {
//         if (thread.valid()) {
//             thread.get();
//         }
//     }
// }

// void TcpServer::acceptConnections() {
//     while (m_running) {
//         fd_set readSet = m_masterSet;
//         timeval timeout { 1, 0 };
//         int activity = select(m_maxFd + 1, &readSet, nullptr, nullptr, &timeout);
//         if (activity < 0) continue;

//         if (FD_ISSET(m_serverSocket, &readSet)) {
//             sockaddr_in clientAddr;
//             socklen_t clientLen = sizeof(clientAddr);
//             int clientSocket = accept(m_serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
//             if (clientSocket > 0) {
//                 FD_SET(clientSocket, &m_masterSet);
//                 if (clientSocket > m_maxFd) m_maxFd = clientSocket;
//                 m_clientBuffers[clientSocket] = {};
//             }
//         }

//         for (int fd = 0; fd <= m_maxFd; ++fd) {
//             if (fd != m_serverSocket && FD_ISSET(fd, &readSet)) {
//                 handleClient(fd);
//             }
//         }
//     }
// }

// void TcpServer::handleClient(int clientSocket) {
//     char buffer[1024];
//     ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    
//     if (bytesRead <= 0) {
//         close(clientSocket);
//         FD_CLR(clientSocket, &m_masterSet);
//         m_clientBuffers.erase(clientSocket);
//         return;
//     }

//     m_clientBuffers[clientSocket].insert(m_clientBuffers[clientSocket].end(), buffer, buffer + bytesRead);
//     Message msg(m_clientBuffers[clientSocket].data());  
//     m_clientBuffers[clientSocket].clear();
//     {
//         std::lock_guard<std::mutex> lock(m_queueMutex);
//         m_messageQueue.emplace(clientSocket, msg);
//     }
//     m_queueCV.notify_one();
// }

// void TcpServer::processMessages() {
//     while (m_running) {
//         std::unique_lock<std::mutex> lock(m_queueMutex);
//         m_queueCV.wait(lock, [this]() { return !m_messageQueue.empty() || !m_running; });

//         while (!m_messageQueue.empty()) {
//             auto [clientSocket, msg] = std::move(m_messageQueue.front());
//             m_messageQueue.pop();
//             lock.unlock();

//             Message response = m_handler.handle(msg);
//             send(clientSocket, response.getData().c_str(), response.getData().size(), 0);

//             lock.lock();
//         }
//     }
// }

// bool TcpServer::sendMessage(Message& message) {
//     return false; 
// }

// Message TcpServer::receiveMessage() {
//     return {}; 
// }

// }//namespace ssapi


// #include "ssapi/TcpServer.h"
// #include <iostream>
// #include <cstring>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <fcntl.h>
// namespace ssapi{

// TcpServer::TcpServer(int port, MessageHandlerFunc handler)
//     : m_port(port), m_handler(std::move(handler)) {
//     m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
//     if (m_serverSocket < 0) {
//         std::cerr << "Failed to create socket\n";
//         return;
//     }

//     int opt = 1;
//     setsockopt(m_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

//     sockaddr_in serverAddr{};
//     serverAddr.sin_family = AF_INET;
//     serverAddr.sin_addr.s_addr = INADDR_ANY;
//     serverAddr.sin_port = htons(m_port);

//     if (bind(m_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
//         std::cerr << "Failed to bind socket\n";
//         return;
//     }

//     if (listen(m_serverSocket, SOMAXCONN) < 0) {
//         std::cerr << "Failed to listen on socket\n";
//         return;
//     }
// }

// TcpServer::~TcpServer() {
//     stop();
//     close(m_serverSocket);
// }

// bool TcpServer::start() {

//     std::cout<<"accepting connections"<<std::endl;
//     m_running = true;
//     m_workerThreads.emplace_back(std::async(std::launch::async, &TcpServer::acceptConnections, this));
//     m_workerThreads.emplace_back(std::async(std::launch::async, &TcpServer::processMessages, this));
//     return true;
// }

// void TcpServer::stop() {
//     m_running = false;
//     m_queueCV.notify_all();

//     for (auto& thread : m_workerThreads) {
//         if (thread.valid()) {
//             thread.get();
//         }
//     }
// }

// void TcpServer::acceptConnections() {
//     fd_set readfds;
//     while (m_running) {
//         FD_ZERO(&readfds);
//         FD_SET(m_serverSocket, &readfds);

//         timeval timeout{1, 0};
//         int activity = select(m_serverSocket + 1, &readfds, nullptr, nullptr, &timeout);

//         if (activity < 0 && errno != EINTR) {
//             std::cerr << "Select error\n";
//             break;
//         }

//         if (FD_ISSET(m_serverSocket, &readfds)) {
//             sockaddr_in clientAddr{};
//             socklen_t clientLen = sizeof(clientAddr);
//             int clientSocket = accept(m_serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
//             if (clientSocket < 0) {
//                 std::cerr << "Failed to accept connection\n";
//                 continue;
//             }

//             fcntl(clientSocket, F_SETFL, O_NONBLOCK);

//             m_clientBuffers[clientSocket] = {};
//         }
//     }
// }

// void TcpServer::handleClient(int clientSocket) {
//     char buffer[1024];
//     ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    
//     if (bytesRead <= 0) {
//         close(clientSocket);
//         m_clientBuffers.erase(clientSocket);
//         return;
//     }

//     m_clientBuffers[clientSocket].insert(m_clientBuffers[clientSocket].end(), buffer, buffer + bytesRead);
//     Message msg(m_clientBuffers[clientSocket].data());  
//     m_clientBuffers[clientSocket].clear();

//     {
//         std::lock_guard<std::mutex> lock(m_queueMutex);
//         m_messageQueue.emplace(clientSocket, msg);
//     }
//     m_queueCV.notify_one();
// }

// void TcpServer::processMessages() {
//     while (m_running) {
//         std::unique_lock<std::mutex> lock(m_queueMutex);
//         m_queueCV.wait(lock, [this]() { return !m_messageQueue.empty() || !m_running; });

//         while (!m_messageQueue.empty()) {
//             auto [clientSocket, msg] = std::move(m_messageQueue.front());
//             m_messageQueue.pop();
//             lock.unlock();

//             Message response = m_handler(msg);
//             sendMessage(response);

//             lock.lock();
//         }
//     }
// }

// bool TcpServer::sendMessage(Message& message) {
//     std::string dataToSend = message.getData();
//     int clientSocket = -1; 
//     if (clientSocket < 0) return false;

//     send(clientSocket, dataToSend.c_str(), dataToSend.size(), 0);
//     return true;
// }

// Message TcpServer::receiveMessage() {
//     return {}; // Не используется в сервере
// }


// }