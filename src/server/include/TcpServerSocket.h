
#pragma once
#include <netinet/in.h>
#include "ssapi/Message.h"

#include <iostream>

class TcpServerSocket {

        // using MessagesQueue = std::queue<std::pair<int, Message>>;

    public:
        TcpServerSocket(int port, std::queue<std::pair<int, Message>>& clients);
        TcpServerSocket(int port);
        ~TcpServerSocket();
        Message receiveMessage(int clientSocket);
        bool sendMessage(int clientSocket, const Message& message);
        int acceptConnection();

    private:
        //methods
        int createServerSocket();
        sockaddr_in initServStruct(int port);
        void bindPort(int serverSocket, sockaddr_in& serverAddr);
        void closeSocket(int socket);

        void listenConnections();
        void listenAndAcceptConnections(int serverSocket, std::queue<std::pair<int, Message>> &clients);
        void listenAndAcceptConnections(std::queue<std::pair<int, Message>>& clients);

        // fields
        int m_serverSocket;
        sockaddr_in m_serverAddr;
        bool m_isRunning;
        std::mutex m_mtx;
        std::condition_variable m_condition;
};
