

#include "ssapi/TcpSocketServer.h"


TcpSocketServer::TcpSocketServer(int port):m_port(port){}

TcpSocketServer::~TcpSocketServer(){}

void TcpSocketServer::start() {
    m_network.Socket();
    m_network.Bind(m_port);
    m_network.SetSocketOptions();
    m_network.Listen();

    while(true){
        m_network.Accept();
    }
}

void TcpSocketServer::stop() { 
    m_network.Close();
}


bool TcpSocketServer::sendMessage(Message &message) {
    return true;
}
Message TcpSocketServer::receiveMessage() {
    return Message();
}


bool TcpSocketServer::sendMessage(int socket ,Message &message) {
    return true;
}
Message TcpSocketServer::receiveMessage(int socket) {
    return Message();
}

