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
}

Message MessageHandler::handle(const Message& message)
{
    Message respMessage {" "};
    switch (message.getType())
    {
    case MessageType::echo:
        respMessage = message;
        break;

    case MessageType::task1: {
        m_taskProcessor = new TaskProcessor_1;

        std::string inData = message.getData();
        std::string outData = m_taskProcessor -> execute(inData);
        
        respMessage.setType(MessageType::task1);
        respMessage.setData(outData.c_str());
        delete m_taskProcessor;
        m_taskProcessor = nullptr;
    }
    break;

    case MessageType::task2:{
            m_taskProcessor = new TaskProcessor_2;

            std::string inData = message.getData();
            std::string outData = m_taskProcessor -> execute(inData);
            
            respMessage.setType(MessageType::task2);
            respMessage.setData(outData.c_str());
            delete m_taskProcessor;
            m_taskProcessor = nullptr;
        }
        break;
    case MessageType::task4:{
            m_taskProcessor = new TaskProcessor_4;

            std::string inData = message.getData();
            std::string outData = m_taskProcessor -> execute(inData);
            
            respMessage.setType(MessageType::task2);
            respMessage.setData(outData.c_str());
            
            delete m_taskProcessor;
            m_taskProcessor = nullptr;
        }
    break;

    default:
        respMessage = "Unsupported message type\n";
        break;
    }
    return respMessage;
}
