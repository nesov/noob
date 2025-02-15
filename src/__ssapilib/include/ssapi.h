#pragma once 

#include "utils.h"

namespace ssapi{
    namespace client {
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
            ssapi::sockaddr_inn m_serv;
        };
    }//namespace client

    namespace server{
        class TCPServer {
         public:
            explicit TCPServer(int port);
            TCPServer() = delete;
            ~TCPServer();

            int listen_();
            int bind_(int port);
            int accept_();

            void receiveMessage(Message&);
            void sendMessage(Message&);

        
        private:
            int m_port;
            int m_server_fd;
            int m_client_fd;
            ssapi::sockaddr_inn m_serv;

            int init();

        };
    }   //namespace server
} // namespace ssapi   