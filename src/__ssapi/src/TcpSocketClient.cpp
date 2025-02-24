
#include "ssapi/TcpSocketClient.h"


TcpSocketClient::TcpSocketClient(std::string host, int port) : m_host(host), m_port(port){ }

TcpSocketClient::~TcpSocketClient(){}

void TcpSocketClient::start(){
    m_network.Socket();
    m_network.Connect(m_host.c_str(), m_port);
}

void TcpSocketClient::stop(){
    m_network.Close();
}

bool TcpSocketClient::sendMessage(Message &message) {
    m_network.sendMessage(m_network.getSocket(), message);
    return true;
}
Message TcpSocketClient::receiveMessage() {
    return m_network.receiveMessage(m_network.getSocket());
}

bool TcpSocketClient::sendMessage(int socket ,Message &message) {
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
