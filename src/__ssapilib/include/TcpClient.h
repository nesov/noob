#pragma once 

#include "Message.h"
#include "Utils.h"

class TCPClient {
    public:
       int connect_();
       void receiveMessage(Message&);
       void sendMessage(Message&);
       
       explicit TCPClient(const char*,int);
       TCPClient() = delete;
       ~TCPClient();

    private:
       const char* m_host;
       int m_port; 
       int m_client_fd;
       int m_connection_status;
       int init(const char*, int); 
       sockaddr_inn m_serv;
   };
