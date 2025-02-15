
#include "ssapi.h"
#include "utils.h"

namespace ssapi{
    namespace server {
        constexpr uint8_t kMaxConnections {5};

        TCPServer::TCPServer (int port) :m_port(port) {
            init();
        }

        TCPServer::~TCPServer(){
            close(m_server_fd);
        }

        
        int TCPServer::listen_(){
            if (listen(m_server_fd, kMaxConnections) < 0) {
                std::cerr << "Listening error\n";
                close(m_server_fd);
                return -1;
            }
            std::cout << "Server is up and running on : " << m_port << "...\n";
            return 0;
        }

        int TCPServer::accept_(){
            sockaddr_in client_address;
            socklen_t client_len = sizeof(client_address);
    
            m_client_fd = accept(m_server_fd, (sockaddr*)&client_address, &client_len);
            if (m_client_fd < 0) {
                std::cerr << "Accept connection error\n";
                close(m_server_fd);
                return -1;
            } else {
                std::cout << "New connection is accepted\n" ;
            }
            return 0;
        }

        int TCPServer::bind_(int port){
            if (bind(m_server_fd, (sockaddr*)&m_serv, sizeof(m_serv)) < 0) {
                std::cerr << "Socket bind error\n";
                close(m_server_fd);
                return -1;
            }
            return 0;
        }

        void TCPServer::receiveMessage(Message&){}
        void TCPServer::sendMessage(Message&){}

        int TCPServer::init(){
            m_server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

            if (m_server_fd == -1) {
                std::cerr << "Socket creation error\n";
                return -1;    
            } else {
                std::cerr << "Socket has been created\n";
            }
        
            int opt = 1;
            if (setsockopt(m_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
                std::cerr << "SO_REUSEADDR setting error\n";
                close(m_server_fd);
                return -1;
            }
        
            std::memset(&m_serv.server_address, 0, sizeof(m_serv));
            m_serv.server_address.sin_family = AF_INET;
            m_serv.server_address.sin_addr.s_addr = INADDR_ANY;
            m_serv.server_address.sin_port = htons(m_port);

            return 0;
        
        }


    }
}