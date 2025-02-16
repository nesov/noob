#pragma once 

#include "Message.h"
#include "Utils.h"

class TcpServer {
    public:
       explicit TcpServer(int port);
       TcpServer() = delete;
       ~TcpServer();

       int listen_();
       int bind_(int port);
       int accept_();

       void receiveMessage(Message&);
       void sendMessage(Message&);

   private:
       int m_port;
       int m_server_fd;
       int m_client_fd;
       sockaddr_inn m_serv;
       int init();
   };