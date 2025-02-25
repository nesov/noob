
#include <iostream>
#include <string>

#include "ssapi/TcpSocketClient.h"
#include "ssapi/INetworkService.h"
#include "ssapi/Message.h"

#include "utils.h"

extern void welcomeServerScreen();

void clearScreen() {
    system("clear");
}

int selectTaskDialog() {
    int choice = 0;
    std::cout
    <<"+-----------+"<<"\n"
    <<"| "<<"Task 1 - 1"<<"|\n"
    <<"| "<<"Task 2 - 2"<<"|\n"
    <<"| "<<"Task 4 - 4"<<"|\n"
    <<"+-----------+\n"
    <<"| "<<"Exit -(-1)"<<"|\n"
    <<"+----------+"<<"\n";
    std::cout<< "Select task to process: ";
    std::cin >> choice;
    std::cin.ignore();
    return choice;
}


bool claerScreenDialog() {
    bool result;
    char choice;
    std::cout << "Want to play again Y/n : "; 
    std::cin >> choice;
    std::cin.ignore();
    
    switch (choice){
        case 'Y':
            clearScreen();
            result = true;
            break;
        case 'n':
            clearScreen();
            result = false;
            break;
        default:
            result = false;
            break;
    }
    return result;
}


std::string enterTextDialog() {
    std::cout << "Enter message text: ";
    std::string text;
    getline(std::cin, text);
    return text;
}

bool composeMessageAndSend(int task, std::string& text){
    if (task < 0){
        std::cout<< "Message is not sent"<<std::endl;
        return false;
    }
    Message message;
    message.setType(static_cast<MessageType>(task));
    message.setData(text.c_str()); 
    {
        INetworkService* service = new TcpSocketClient("127.0.0.1", 8080);
        service -> start();
        service -> sendMessage(message);
        Message fromServ = service -> receiveMessage();
        service-> stop();
        delete service;
        std::cout<<"Out Message : "<< message <<std::endl;
        std::cout<<"Inc Message : "<< fromServ <<std::endl;
    }   
    return true;
}

void run() {
    welcomeScreen("Client");
    bool isRunning = true;
    while(isRunning) {
        int type = -1;
        std::string data;
        type = selectTaskDialog();
        if (type == -1 ){
            break;
        } else {
            data = enterTextDialog();
            if (composeMessageAndSend(type, data) == false) break;
        }
        isRunning = claerScreenDialog();
    }
}




int main() {
    run();
    return 0;
}
