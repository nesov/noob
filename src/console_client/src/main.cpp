
#include <iostream>

#include "ssapi/TcpSocketClient.h"
#include "ssapi/INetworkService.h"




int main() {

    INetworkService* service = new TcpSocketClient("127.0.0.1", 8080);

    while(true){
        service-> start();
        std::cout<< "Enter message text: "<<std::endl;
        std::string text;
        getline(std::cin, text);

        Message toSend(text.c_str());
        service-> sendMessage(toSend);
        Message fromServ = service-> receiveMessage();
        std::cout<<"Server responce: "<< fromServ;
        service-> stop();
        if (text.compare("exit") == 0) {
            break;
        }
     }
     delete service;

    return 0;
}
