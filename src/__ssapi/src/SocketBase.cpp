
#include "ssapi/SocketBase.h"

void SocketBase::Socket(){
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0) {
        std::cout << "Socket: " << strerror(errno)<< std::endl;
        Close();
    }
}

void SocketBase::SetSocketOptions(){
    int opt = 1;
    if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cout << "Set Socket Options: "<< strerror(errno)<<std::endl;
        Close();
    }
}

void SocketBase::Bind(int port) {
    std::memset(&m_address,0,sizeof(sockaddr_in));
    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(port);
    m_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(m_socket, (struct sockaddr *)&m_address, sizeof(m_address)) < 0) {
            std::cout << "Bind: " << strerror(errno)<< std::endl;
            Close();
    }
}

void SocketBase::Listen(){
    if(listen(m_socket, SOMAXCONN) < 0){
        std::cout<<"Listen: "<<strerror(errno)<<std::endl;
        Close();
    }
}

int SocketBase::Accept(){
    sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    std::memset(&clientAddr,0,sizeof(sockaddr_in));
    std::cout << "Waiting for connections...\n";
    int clientSock = accept(m_socket, (struct sockaddr *)&clientAddr, &clientLen);
   
    if (clientSock < 0){
        std::cout << "Accept: " << strerror(errno) << std::endl;
        close(clientSock);
        return -1;     
    } 
    // identifyConnection(clientSock);
    return clientSock;   
}

void SocketBase::Connect(const char* host, int port){
    std::memset(&m_address, 0, sizeof(sockaddr_in));
    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(port);
    inet_pton(AF_INET, host, &m_address.sin_addr);

    if (connect(m_socket, (sockaddr *)&m_address, sizeof(m_address)) < 0) {
        std::cout << "Connect: " << strerror(errno) << std::endl;
        Close();
    }
}
//Need to be fixed
void SocketBase::Send(int socket, const void* data, size_t dataSize){
    ssize_t bytesSent = send(socket, data, dataSize, 0);
    if (bytesSent < dataSize) {
        std::cout << "Send: " << strerror(errno)<< std::endl;
    }
}

//Need to be fixed
void SocketBase::Receive(int socket, void* data, size_t dataSize) {
    ssize_t bytesReceive = recv(m_socket, data, dataSize, 0);
    if (bytesReceive < dataSize) {
        std::cerr << "Receive: " << strerror(errno)<<std::endl;
    }
}

void SocketBase::Close() {
    shutdown(m_socket, SHUT_RDWR);
    close(m_socket);
}

void SocketBase::Close(int socket){
    shutdown(m_socket, SHUT_RDWR);
    close(socket);
}

int SocketBase::getSocket(){
    return m_socket;
}

void SocketBase::identifyConnection(int socket){
    sockaddr_in clientAdd;
    socklen_t addrLen = sizeof(clientAdd);
    
    if (getpeername(socket, (sockaddr*)&clientAdd, &addrLen) == 0) {
        char ip_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAdd.sin_addr, ip_str, sizeof(ip_str));
        int clientPort = ntohs(clientAdd.sin_port);
        std::cout << "ip: " << ip_str << ":" << clientPort <<std::endl;
    } else {
        std::cout << "Getting client info errror\n"<<strerror(errno);
    }
}


bool SocketBase::sendMessage(int socket, const Message &message)
{
    uint8_t type = static_cast<uint8_t>(message.getType());
    uint32_t dataSize = message.getData().size();

    if (send(socket, &type, sizeof(type), 0) == -1) {
        std::cerr << "Error receiving data" <<strerror(errno)<<std::endl;
        return false;
    }
    if (send(socket, &dataSize, sizeof(dataSize), 0) == -1) {
        std::cerr << "Error receiving data" <<strerror(errno)<<std::endl;
        return false;
    }
    if (send(socket,message.getData().c_str(), dataSize, 0) == -1) {
        std::cerr << "Error receiving data" <<strerror(errno)<<std::endl;
        return false;
    }
    return true;
}

Message SocketBase::receiveMessage(int socket) {
    uint8_t type {0};
    uint32_t dataSize{0};
    
    if (recv(socket, &type, sizeof(type), 0) <= 0) {
        std::cerr << "Error receiving data" <<strerror(errno)<<std::endl;
    }
    if (recv(socket, &dataSize, sizeof(dataSize), 0) <= 0) {
        std::cerr << "Error receiving data" <<strerror(errno)<<std::endl;
    }
    std::string data(dataSize, '\0');
    if (recv(socket, data.data(), dataSize, 0) <= 0) {
        std::cerr << "Error receiving data" <<strerror(errno)<<std::endl;
    }
    return Message(static_cast<MessageType>(type), data);
}
