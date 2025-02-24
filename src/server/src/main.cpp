// #include "ServerApplication.h"
// #include "ssapi/INetworkService.h"
#include "ssapi/TcpSocketServer.h"
#include "ssapi/INetworkService.h"


int main() {
    Message respMessage {"Resp from server"};
    INetworkService* service = new TcpSocketServer(8080);
    service -> start();
    
    while(true){
        int connection = service -> Accept();
        
        Message incomingMessage =  service -> receiveMessage(connection);

        std::cout<<"Incoming Message : "<< incomingMessage;
        service -> sendMessage(connection, respMessage);
    }


    return 0;
}