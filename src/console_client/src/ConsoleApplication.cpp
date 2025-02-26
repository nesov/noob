
#include "ConsoleApplication.h"
#include <ssapi/Message.h>

ConsoleApplication::~ConsoleApplication(){
    if (m_network){
        delete m_network ;
        m_network = nullptr;
    }
}
    



void ConsoleApplication::run(){
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

void ConsoleApplication::clearScreen() {
    std::system("clear");
}

int ConsoleApplication::selectTaskDialog() {
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


bool ConsoleApplication::claerScreenDialog() {
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

std::string ConsoleApplication::enterTextDialog() {
    std::cout << "Enter message text: ";
    std::string text;
    getline(std::cin, text);
    return text;
}

bool ConsoleApplication::composeMessageAndSend(int task, std::string& text){
    if (task < 0){
        std::cout<< "Message is not sent"<<std::endl;
        return false;
    }
    Message message;
    message.setType(static_cast<MessageType>(task));
    message.setData(text.c_str()); 
    {
        m_network = (new NetworkServiceFactory) -> createNetworkService(true, "127.0.0.1", 8080);
        
        m_network -> start();
        m_network -> sendMessage(message);
        Message fromServ = m_network -> receiveMessage();
        m_network -> stop();
        delete m_network;

        std::cout<<"Out Message : "<< message <<std::endl;
        std::cout<<"Inc Message : "<< fromServ <<std::endl;
    }   
    return true;
}

void show(const Message& sent, const Message& received){
    std::cout<<"Out Message : "<< sent <<std::endl;
    std::cout<<"Inc Message : "<< received <<std::endl;
}


void show(const std::string& sent, const std::string& received){
    std::cout<<"Out Message : "<< sent <<std::endl;
    std::cout<<"Inc Message : "<< received <<std::endl;
}














// bool composeMessageAndSend(int task, std::string& text){
//     if (task < 0){
//         std::cout<< "Message is not sent"<<std::endl;
//         return false;
//     }
//     Message message;
//     message.setType(static_cast<MessageType>(task));
//     message.setData(text.c_str()); 
//     {
//         INetworkService* service = new TcpSocketClient("127.0.0.1", 8080);
//         service -> start();
//         service -> sendMessage(message);
//         Message fromServ = service -> receiveMessage();
//         service-> stop();
//         delete service;
//         std::cout<<"Out Message : "<< message <<std::endl;
//         std::cout<<"Inc Message : "<< fromServ <<std::endl;
//     }   
//     return true;
// }



// void run() {
//     welcomeScreen("Client");
//     bool isRunning = true;
//     while(isRunning) {
//         int type = -1;
//         std::string data;
//         type = selectTaskDialog();
//         if (type == -1 ){
//             break;
//         } else {
//             data = enterTextDialog();
//             if (composeMessageAndSend(type, data) == false) break;
//         }
//         isRunning = claerScreenDialog();
//     }
// }




