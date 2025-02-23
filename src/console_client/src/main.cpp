
#include <iostream>

#include <ssapi/TcpClient.h>

int main() {
    while(true){
        std::cout<< "Enter message text: "<<std::endl;
        std::string text;
        getline(std::cin, text);

        Message requestMessage (text.c_str());
        requestMessage.setType(MessageType::task2);

        TcpClient* netclient = new TcpClient("127.0.0.1", 8080);
        netclient -> start();
        netclient -> sendMessage(requestMessage);
        Message responceMessage = netclient -> receiveMessage();
        netclient -> stop();
        delete netclient;
        std::cout<<"Responce Message"<< responceMessage<< std::endl;
     }
    
    // std::cout<<"Hello world form console client"<<std::endl;
    return 0;
}
