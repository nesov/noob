
#include "ConsoleApplication.h"
#include <ssapi/Message.h>

#include "MainDialog.h"
#include "WantPlayAgainDialog.h"

ConsoleApplication::ConsoleApplication(){
    m_network = (new NetworkServiceFactory) -> createNetworkService(true,"127.0.0.1",8080);
    m_dialogs.emplace_back(new MainDialog);
    m_dialogs.emplace_back(new WantPlayAgainDialog);
}


ConsoleApplication::~ConsoleApplication(){
    if (m_network){
        delete m_network ;
        m_network = nullptr;
    }

    for (auto& dialog: m_dialogs){
        if (dialog){
            delete dialog;
            dialog = nullptr;
        }
    }
}
    
int  ConsoleApplication::run(){
    while (true){
        auto dialog = static_cast<MainDialog*>(m_dialogs[0]);
        dialog->show();

        int type = dialog -> enterType();
        std::string data = dialog -> enterText();
        composeMessageAndSend(type, data);

        auto dialog1 = static_cast<WantPlayAgainDialog*>(m_dialogs[1]);
        dialog1 -> show();
        if (dialog1 -> yesNo()){
            continue;
        } else {
            break;
        }
    }
    return 0;
}






    // bool isRunning = true;
    // while(isRunning) {
    //     int type = -1;
    //     std::string data;
    //     type = selectTaskDialog();
    //     if (type == -1 ){
    //         break;
    //     } else {
    //         data = enterTextDialog();
    //         if (composeMessageAndSend(type, data) == false) break;
    //     }
    //     isRunning = claerScreenDialog();
    // }




// void ConsoleApplication::clearScreen() {
//     std::system("clear");
// }

// int ConsoleApplication::selectTaskDialog() {
//     int choice = 0;
//     std::cout
//     <<"+-----------+"<<"\n"
//     <<"| "<<"Task 1 - 1"<<"|\n"
//     <<"| "<<"Task 2 - 2"<<"|\n"
//     <<"| "<<"Task 4 - 4"<<"|\n"
//     <<"+-----------+\n"
//     <<"| "<<"Exit -(-1)"<<"|\n"
//     <<"+----------+"<<"\n";
//     std::cout<< "Select task to process: ";
//     std::cin >> choice;
//     std::cin.ignore();
//     return choice;
// }


// bool ConsoleApplication::claerScreenDialog() {
//     bool result;
//     char choice;
//     std::cout << "Want to play again Y/n : "; 
//     std::cin >> choice;
//     std::cin.ignore();
    
//     switch (choice){
//         case 'Y':
//             //clearScreen();
//             result = true;
//             break;
//         case 'n':
//             //clearScreen();
//             result = false;
//             break;
//         default:
//             result = false;
//             break;
//     }
//     return result;
// }



bool ConsoleApplication::composeMessageAndSend(int task, std::string& text){
    if (task < 0){
        std::cout<< "Task number can't be negative."<<std::endl;
        return false;
    }
    Message message;
    message.setType(static_cast<MessageType>(task));
    message.setData(text.c_str()); 
    Message fromServ;

    if (m_network -> start()){
        m_network -> sendMessage(message);
        fromServ = m_network -> receiveMessage();
        m_network -> stop();
    } else {
        std::cerr<< "Message is not sent due to connecting issues, Make sure the server is running." << std::endl;
        return false;
    }
    std::cout<<"Out Message : "<< message <<std::endl;
    std::cout<<"Inc Message : "<< fromServ <<std::endl;

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
