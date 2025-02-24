
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

// bool TcpSocketClient::sendMessage(Message &message) {
//     // int socket = m_network.getSocket();
//     // int messageSize = message.size();
//     // m_network.Send(socket,(char* )&messageSize, messageSize);
//     // m_network.Send(socket,message.)
//     return true;
// }
// Message TcpSocketClient::receiveMessage() {
//     return Message();
// }

