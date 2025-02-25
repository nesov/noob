#include "ssapi/TcpSocketServer.h"
#include "ssapi/INetworkService.h"
#include "MessageHandler.h"

void welcomeScreen(const char* who) {
    std::cout << std::endl
        << "+-+  +-+ +------+ +------+ +-----\" \n"
        << "|  \\ | | | +--+ | | +--+ | | +--+ |\n"
        << "|   \\| | | |  | | | |  | | | +--+/ \n"
        << "| |\\   | | |  | | | |  | | | +--+\\ \n"
        << "| | \\  | | +--+ | | +--+ | | +--+ |\n"
        << "+-+  +-+ +------+ +------+  +----/ \n"
        << std::endl;

    std::cout << "Terminal TCP "<< who <<"\n"
              << "Coded by Niesov Oleksandr \n"
              << std::endl;
}
int main() {
    welcomeScreen("Single File - Server");
    
    INetworkService* service = new TcpSocketServer(8080);
    MessageHandler handler;
    service -> start();
    
    while(true){
        int connection = service -> Accept();
        Message incomingMessage =  service -> receiveMessage(connection);
        Message respMessage  = handler.handle(incomingMessage);
        service -> sendMessage(connection, respMessage);

        std::cout<<"Inc Message : "<< incomingMessage <<std::endl;
        std::cout<<"Out Message : "<< respMessage <<std::endl;;
    }
    return 0;
}