#pragma once

#include <vector>
#include <mutex>
#include <future>
#include <netinet/in.h> 

class TcpServer {
public:
    TcpServer(int port);
    ~TcpServer();

    void start();
    void stop();
    void broadcastMessage(const std::string& message);

private:
    void acceptClients();
    void handleClient(int clientSocket);

    int m_serverSocket;
    int m_port;
    std::vector<int> m_clients;
    std::mutex m_mutex;
    bool m_running;
    std::future<void> m_future;
};
