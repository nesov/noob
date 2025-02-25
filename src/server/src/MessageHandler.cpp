#include <string>
#include <iostream>

#include "MessageHandler.h"

#include "ssapi/Message.h"
#include "proc/TaskProcessor_1.h"
#include "proc/TaskProcessor_2.h"
#include "proc/TaskProcessor_4.h"


MessageHandler::~MessageHandler(){
    if (m_taskProcessor) {
        delete m_taskProcessor;
    }
    m_taskProcessor = nullptr;
}

Message MessageHandler::handle(const Message& message) {
    Message respMessage {" "};

    switch (message.getType()) {
    case MessageType::echo:
        respMessage = message;
        break;

    case MessageType::task1: {
        m_taskProcessor = new TaskProcessor_1;

        // respMessage.setType(MessageType::task1);
        // respMessage.setData( m_taskProcessor -> execute(message.getData()).c_str());

        std::string inData = message.getData();
        std::string outData = m_taskProcessor -> execute(inData);
        
        respMessage.setType(MessageType::task1);
        respMessage.setData(outData.c_str());
        delete m_taskProcessor;
    }
    break;

    case MessageType::task2:{
        m_taskProcessor = new TaskProcessor_2;

        std::string inData = message.getData();
        std::string outData = m_taskProcessor->execute(inData);

        respMessage.setType(MessageType::task2);
        respMessage.setData(outData.c_str());

        delete m_taskProcessor;
    }
    break;
    case MessageType::task4: {
        m_taskProcessor = new TaskProcessor_4;

        std::string inData = message.getData();
        std::string outData = m_taskProcessor -> execute(inData);

        respMessage.setType(MessageType::task4);
        respMessage.setData(outData.c_str());

        delete m_taskProcessor;
    }
    break;

    default:
        respMessage = "Unsupported message type\n";
        break;
    }
    return respMessage;
}

