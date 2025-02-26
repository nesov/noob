
#include "ssapi/TcpSocketClient.h"


TcpSocketClient::TcpSocketClient(std::string host, int port) : m_host(host), m_port(port){ }

TcpSocketClient::~TcpSocketClient(){}

bool TcpSocketClient::start(){
    m_network.Socket();
    return m_network.Connect(m_host.c_str(), m_port);
}

void TcpSocketClient::stop(){
    m_network.Close();
}

bool TcpSocketClient::sendMessage(const Message &message) {
    m_network.sendMessage(m_network.getSocket(), message);
    return true;
}
Message TcpSocketClient::receiveMessage() {
    return m_network.receiveMessage(m_network.getSocket());
}

bool TcpSocketClient::sendMessage(int socket, const Message &message) {
    std::cout << "Operation is not supported for client\n";
    return true;
}
Message TcpSocketClient::receiveMessage(int socket) {
    std::cout << "Operation is not supported for client\n";
    return Message();
}

int TcpSocketClient::Accept(){
    std::cout << "Operation is not supported for client\n";
    return -1;
}

bool TcpSocketClient::isConnected() {   
    return m_network.isConnected();
}
