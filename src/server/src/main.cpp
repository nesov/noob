
// #include "AsyncServer.h"
#include "ssapi/TcpClient.h"
#include "ssapi/TcpServer.h"
#include "ssapi/INetworkService.h" 
#include "ssapi/Consts.h"



#include <iostream>

int main() {
   
    // INetwork* netservice = new ssapi::TcpClient(ssapi::kHost,ssapi::kPort);

    INetworkService* netservice =  new ssapi::TcpServer(ssapi::kPort);

    // Message mes = {"Hello world!\n"};

    // std::cout << mes.size();

    // for (int i = 0; i < 10; i++ ){
    //     netservice -> sendMessage(mes);
    // }

    // delete netservice;

    Connection conn, conn1, conn2;
    Message message = {"hello"}, message1 = {"byby"}, message2 ={"Hasta Lavista"}; 

    std::queue<std::pair<Connection, Message>> line;
    // line.push(std::make_pair(conn,message));
    // line.push(std::make_pair(conn1,message1));
    // line.push(std::make_pair(conn2,message2));

    line.push(std::make_pair(std::move(conn), std::move(message)));
    line.push(std::make_pair(std::move(conn1), std::move(message1)));
    line.push(std::make_pair(std::move(conn2), std::move(message2)));


    while (!line.empty()) {
        std::cout << "Socket: " << line.front().first.clientSocket
                  << "Message Data: " << line.front().second.getData() << std::endl;
        line.pop();
    }
    std::cout << "Current Line size: " << line.size() << std::endl;

 
    return 0;
}
