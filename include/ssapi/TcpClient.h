#pragma once



#include <netinet/in.h> 

#include <string>
#include <mutex>

#include "ssapi/INetwork.h"
#include "ssapi/Message.h"
#include "ssapi/Connection.h"

class TcpClient : public INetwork {
public:
    TcpClient(const std::string& serverIp, int port);
    ~TcpClient();
    
    void start();
    void stop();

    void sendMessage(const Message& );
    Message receiveMessage();

private:
    Connection connection;
    int m_socket;
    struct sockaddr_in m_serverAddr;
    std::mutex m_mutex;

    bool connectToServer();
    void disconnect();
};
