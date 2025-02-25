#include <string>
#include <iostream>

#include "MessageHandler.h"
#include "ssapi/Message.h"

#include "proc/TaskProcessor_1.h"

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
    case MessageType::task1: {
        m_taskProcessor = new TaskProcessor_1;

        std::string inData = message.getData();
        std::string outData = m_taskProcessor -> execute(inData);
        
        respMessage.setType(MessageType::task1);
        respMessage.setData(outData.c_str());
        delete m_taskProcessor;
    }

    break;
    case MessageType::task2:
        respMessage = "task2";
        break;

    case MessageType::echo:
        respMessage = message;
        break;

    default:
        respMessage = "Unsupported message type\n";
        break;
    }
    return respMessage;
}
