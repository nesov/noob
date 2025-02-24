
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
        std::cout<< "\r";
        service-> stop();
        if (text.compare("exit") == 0) {
            break;
        }
           

        // Message requestMessage (text.c_str());
        // requestMessage.setType(MessageType::task2);

        // TcpClient* netclient = new TcpClient("127.0.0.1", 9090);
        // netclient -> start();
        // netclient -> sendMessage(requestMessage);
        // Message responceMessage = netclient -> receiveMessage();
        // netclient -> stop();
        // delete netclient;
        // std::cout<<"Responce Message"<< responceMessage<< std::endl;
     }
     delete service;

    return 0;
}
