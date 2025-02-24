
#include "ssapi/SocketBase.h"

SocketBase::SocketBase() { }
SocketBase::~SocketBase() { }

void SocketBase::Socket(){
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0) {
        std::cout << "Creating socket failed" << strerror(errno)<<std::endl;
        Close();
    }
}

void SocketBase::SetSocketOptions(){
    int opt = 1;
    if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cout << "SO_REUSEADDR setting fail : "<<strerror(errno)<<std::endl;
        Close();
    }
}

void SocketBase::Bind(int port) {
    std::memset(&m_address,0,sizeof(sockaddr_in));
    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(port);
    m_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(m_socket, (struct sockaddr *)&m_address, sizeof(m_address)) < 0) {
            std::cout << "Bind failed :" <<strerror(errno)<< std::endl;
            Close();
    }
}

void SocketBase::Listen(){
    if(listen(m_socket, SOMAXCONN) < 0){
        std::cout<<"Listen failed : "<<strerror(errno)<<std::endl;
        Close();
    }
}

int SocketBase::Accept(){
    sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    std::memset(&clientAddr,0,sizeof(sockaddr_in));
    std::cout<<"Accepting...\n";
    int clientSock = accept(m_socket, (struct sockaddr *)&clientAddr, &clientLen);
    if (clientSock < 0){
        std::cout << "Accept failed :" << strerror(errno) << std::endl;
        close(clientSock);
        return -1;     
    } 
    return clientSock;   
}

void SocketBase::Connect(const char* host, int port){
    std::memset(&m_address, 0, sizeof(sockaddr_in));
    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(port);
    inet_pton(AF_INET, host, &m_address.sin_addr);

    if (connect(m_socket, (sockaddr *)&m_address, sizeof(m_address)) < 0) {
        std::cout << "Connect failed : " << strerror(errno) << std::endl;
        Close();
    }
}

void SocketBase::Send(int socket, const char* data, size_t dataSize){
    ssize_t bytesSent = send(socket, &data, dataSize, 0);
    if (bytesSent < dataSize) {
        std::cout << "Sending failed : "<<strerror(errno)<< std::endl;
        Close();
    }
}

void SocketBase::Receive(int socket, char* data, size_t dataSize) {
    ssize_t bytesReceive = recv(m_socket, &data, dataSize, 0);
    if (bytesReceive < dataSize) {
        std::cerr << "Error receiving data" <<strerror(errno)<<std::endl;
        Close();
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
