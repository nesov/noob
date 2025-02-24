// #include "TcpServerSocket.h"
// #include <unistd.h>


// TcpServerSocket::TcpServerSocket(int port) {
//     m_serverSocket  = createServerSocket();
//     m_serverAddr    = initServStruct(port);
//     bindPort(m_serverSocket, m_serverAddr);
//     listenConnections();
// }

// TcpServerSocket::TcpServerSocket(int port, std::queue<std::pair<int, Message>>& clients) {
//     m_serverSocket  = createServerSocket();
//     m_serverAddr    = initServStruct(port);
//     bindPort(m_serverSocket, m_serverAddr);
//     listenAndAcceptConnections(m_serverSocket, clients);
// }

// TcpServerSocket::~TcpServerSocket(){
//     closeSocket(m_serverSocket);
// }

// int TcpServerSocket::createServerSocket() {
//     int sock = socket(AF_INET, SOCK_STREAM, 0);
//     if (sock < 0) {
//         std::cout << "Error creating socket" << strerror(errno)<<std::endl;
//         close(sock);
//         return -1;
//     }

//     int opt = 1;
//     if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
//         std::cout << "SO_REUSEADDR setting error"<<strerror(errno)<<std::endl;
//         m_isRunning = false;
//         closeSocket(sock);
//         return -1;
//     }
//     return sock;
// }

// sockaddr_in TcpServerSocket::initServStruct(int port) {
//     struct sockaddr_in serverAddr; 
//     std::memset(&serverAddr,0,sizeof(sockaddr_in));
//     serverAddr.sin_family = AF_INET;
//     serverAddr.sin_port = htons(port);
//     serverAddr.sin_addr.s_addr = INADDR_ANY;
//     return serverAddr;
// }

// void TcpServerSocket::bindPort(int serverSocket, sockaddr_in& serverAddr ){
//     if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
//         std::cout << "Bind failed" <<strerror(errno)<< std::endl;
//         closeSocket(m_serverSocket);
//         m_isRunning = false;
//     }
//     m_isRunning = true;
// }

// void TcpServerSocket::closeSocket(int socket) {
//     m_isRunning = false;
//     shutdown(socket,SHUT_RDWR);
//     close(socket);
// }

// void TcpServerSocket::listenConnections(){
//     if(listen(m_serverSocket, 10) < 0){
//         std::cout<<"Fail to listen: "<<strerror(errno)<<std::endl;
//         closeSocket(m_serverSocket);
//     }
        
// }

// int TcpServerSocket::acceptConnection(){
//     // sockaddr_in clientAddr{};
//     // socklen_t clientLen = sizeof(clientAddr);
//     // int clientSock = accept(m_serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
//     int clientSock = accept(m_serverSocket, nullptr, nullptr);
//     if (clientSock < 0){ 
//         std::cout << "Accept failed "<< strerror(errno)<<std::endl;
//         closeSocket(clientSock);
//     }
//     return clientSock;
// }


// void TcpServerSocket::listenAndAcceptConnections(int serverSocket, std::queue<std::pair<int, Message>>& clients){    
//     listen(serverSocket, SOMAXCONN);
//     std::cout << "Waiting for connections..." << std::endl;
//     while (true) {
//         sockaddr_in clientAddr{};
//         std::memset(&clientAddr,0,sizeof(sockaddr_in));
//         socklen_t clientLen = sizeof(clientAddr);
//         int clientSock = accept(m_serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
//         if (clientSock < 0){
//             std::cout << "Accept failed" << std::endl;
//             closeSocket(clientSock);
//             continue;
//         } else {
//             Message incomingMessage = receiveMessage(clientSock);
//             std::cout<< "Before adding to queue : " << incomingMessage <<std::endl
//                      << "Queue size : "<< clients.size()<< std::endl;
//             clients.emplace(clientSock, incomingMessage);
//         }
//     }
// }


// void TcpServerSocket::listenAndAcceptConnections(std::queue<std::pair<int, Message>>& clients){    
//     listen(m_serverSocket, SOMAXCONN);
//     std::cout << "Waiting for connections..." << std::endl;

//     while (true) {
//         sockaddr_in clientAddr{};
//         socklen_t clientLen = sizeof(clientAddr);
//         int clientSock = accept(m_serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
//         if (clientSock < 0){
//             std::cout << "Accept failed!!!!" << std::endl;
//             closeSocket(clientSock);
//             continue;
//         } else {
//             Message incomingMessage = receiveMessage(clientSock);
       
//             {
//                 // std::lock_guard<std::mutex> lock(m_mtx);
//                 clients.emplace(clientSock, incomingMessage);
//             }
//             // m_condition.notify_one();
//             // need to lock somehow but not

//             std::cout << "After adding to queue : " << incomingMessage << std::endl
//                       << "Queue size : " << clients.size() << std::endl;
//         }
//     }
// }


// Message TcpServerSocket::receiveMessage(int clientSocket){

//     // std::lock_guard<std::mutex> lock(m_mtx);

//     size_t messageSize = 0;
//     ssize_t bytesRead = recv(clientSocket, &messageSize, sizeof(messageSize), 0);
//     if (bytesRead < 0) {
//         std::cerr << "Error receiving size " <<strerror(errno)<< std::endl;
//         closeSocket(clientSocket);
//         return Message();
//     }
//     std::vector<char> buffer(messageSize);
//     bytesRead = recv(clientSocket, buffer.data(), messageSize, 0);
//     if (bytesRead < 0) {
//         std::cerr << "Error receiving data" << std::endl;
//         closeSocket(clientSocket);
//         return Message();
//     } 
//     return Message::deserialize(buffer);

// }

// bool TcpServerSocket::sendMessage(int clientSocket, const Message& message) {

//     // std::lock_guard<std::mutex> lock(m_mtx);

//     std::vector<char> buffer;
//     message.serialize(buffer);
//     size_t messageSize = buffer.size();

//     ssize_t bytesSent = send(clientSocket, &messageSize, sizeof(messageSize), 0);
//     if (bytesSent < 0) {
//         std::cerr << "Error sending size"<<strerror(errno)<< std::endl;
//         closeSocket(clientSocket);
//         return false;
//     }
//     bytesSent = send(clientSocket, buffer.data(), buffer.size(), 0);
//     if (bytesSent < 0) {
//         std::cerr << "Error sending data"<<strerror(errno) << std::endl;
//         closeSocket(clientSocket);
//         return false;
//     }
//     closeSocket(clientSocket);
//     return true;
// }

