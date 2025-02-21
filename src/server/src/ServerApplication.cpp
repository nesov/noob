
#include "ServerApplication.h"
#include "ssapi/TcpServer.h"

ServerApplication::ServerApplication(const int port) {
    m_networkService = new ssapi::TcpServer(port); 
    m_messagehandler = new MessageHandler;
    
}

ServerApplication::~ServerApplication() {
    if (m_messagehandler) {
        delete m_messagehandler;
    }
     
    if (m_networkService){ 
        m_networkService->stop();
        delete m_networkService;
    }
}

void ServerApplication::serve() {
    m_networkService -> start();
    
    while(true) {
        Message messageIn = m_networkService -> receiveMessage();
        Message messageOut = m_messagehandler -> handle(messageIn);
        m_networkService -> sendMessage(messageOut);
    }
}