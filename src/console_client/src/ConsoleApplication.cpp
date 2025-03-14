
#include <ssapi/Message.h>
#include "ConsoleApplication.h"

#include "MainDialog.h"
#include "WantPlayAgainDialog.h"
#include "consts.h"


ConsoleApplication::ConsoleApplication(){
    m_network = (new NetworkServiceFactory) -> createNetworkService(true, kHost, kPort);
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


int  ConsoleApplication::run() {
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


bool ConsoleApplication::composeMessageAndSend(int task, std::string& text) {
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


void show(const Message& sent, const Message& received) {
    std::cout<<"Out Message : "<< sent <<std::endl;
    std::cout<<"Inc Message : "<< received <<std::endl;
}


void show(const std::string& sent, const std::string& received){
    std::cout<<"Out Message : "<< sent <<std::endl;
    std::cout<<"Inc Message : "<< received <<std::endl;
}
