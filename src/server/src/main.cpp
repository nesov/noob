// #include "ServerApplication.h"
#include "ssapi/TcpSocketServer.h"
#include "ssapi/INetworkService.h"
#include "MessageHandler.h"


int main() {
    // Message respMessage; //{"Resp from server"};
    

    INetworkService* service = new TcpSocketServer(8080);
    MessageHandler handler;
    service -> start();
    
    while(true){
        int connection = service -> Accept();
        
        Message incomingMessage =  service -> receiveMessage(connection);
        std::cout<<"Inc Message : "<< incomingMessage;

        Message respMessage  = handler.handle(incomingMessage);
        std::cout<<"Out Message : "<< respMessage;
        service -> sendMessage(connection, respMessage);
    }
    return 0;
}