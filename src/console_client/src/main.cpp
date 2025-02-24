
#include <iostream>

#include "ssapi/TcpSocketClient.h"
#include "ssapi/INetworkService.h"




int main() {

    INetworkService* service = new TcpSocketClient("127.0.0.1", 8080);

    while(true){
        
        std::cout<< "Enter message text: "<<std::endl;
        std::string text;
        getline(std::cin, text);
        Message toSend(text.c_str());
        toSend.setType(MessageType::task1);
        if (text.compare("exit") == 0) {
            break;
        }
        service-> start();
        service -> sendMessage(toSend);
        std::cout<<"OUT message: "<< toSend;
        Message fromServ = service-> receiveMessage();
        std::cout<<"IN message: "<< fromServ;

        
        service-> stop();
    
     }
     delete service;
    return 0;
}
