// #include "ServerApplication.h"
// #include "ssapi/INetworkService.h"
#include "ssapi/TcpSocketServer.h"
#include "ssapi/IAcceptable.h"

int main() {
    // ServerApplication application (9090);
    // application.run();

    // INetworkService* service = new TcpSocketServer(8080);

    Message respMessage {"Resp from server"};

    INetworkService* service = new TcpSocketServer(8080);
    service -> start();
    while(true){
        int connection = service -> Accept();
        Message incomingMessage =  service -> receiveMessage(connection);
        std::cout<<"Incoming Message : "<<incomingMessage;
        service -> sendMessage(respMessage);
    }
    

    

    
    // service -> stop();

    return 0;
}