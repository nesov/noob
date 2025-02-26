#include "ssapi/TcpSocketServer.h"


TcpSocketServer::TcpSocketServer(int port):m_port(port){}

TcpSocketServer::~TcpSocketServer(){}

bool TcpSocketServer::start() {
    m_network.Socket();
    m_network.Bind(m_port);
    m_network.SetSocketOptions();
    m_network.Listen();

    return true;
}

void TcpSocketServer::stop() { 
    m_network.Close();
}


bool TcpSocketServer::sendMessage(const Message &message) {
    std::cout << "Operation is not recommended for Server\n";
    m_network.sendMessage(m_network.getSocket(), message);
    return true;
}
Message TcpSocketServer::receiveMessage() {
    std::cout << "Operation is not recommended for Server\n";
    return m_network.receiveMessage(m_network.getSocket());
}


bool TcpSocketServer::sendMessage(int socket, const Message &message){
    m_network.sendMessage(socket, message);
    return true;
}
Message TcpSocketServer::receiveMessage(int socket) {
    return m_network.receiveMessage(socket);
}

int TcpSocketServer::Accept(){
   return m_network.Accept();
}

bool TcpSocketServer::isConnected() {
    std::cout << "Operation is not recommended for Server\n";
    return (m_network.isConnected());
}
