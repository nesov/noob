// #include "ServerApplication.h"
// #include "ssapi/INetworkService.h"
#include "ssapi/TcpSocketServer.h"
#include "ssapi/IAcceptable.h"

int main() {
    // ServerApplication application (9090);
    // application.run();

    // INetworkService* service = new TcpSocketServer(8080);

    INetworkService* service = new TcpSocketServer(8080);
    service -> start();
    while(true){
        int connection = service -> Accept();
        std::cout<<"Incoming connection : "<<connection;
    }
    

    

    
    // service -> stop();

    return 0;
}