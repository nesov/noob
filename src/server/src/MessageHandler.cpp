
#include <string>
#include <iostream>

#include "MessageHandler.h"

#include "ssapi/Message.h"
#include "proc/TaskProcessorFactory.h"


MessageHandler::~MessageHandler(){
    if (m_taskProcessor) {
        delete m_taskProcessor;
        m_taskProcessor = nullptr;
    }
}


Message MessageHandler::handle(const Message& message) {
    Message respMessage {" "};

    switch (message.getType()) {
    case MessageType::echo:
        respMessage = message;
        break;

    case MessageType::task1: 
    {
        m_taskProcessor = m_processorFactory.createTaskProcessor(static_cast<int>(MessageType::task1));
        respMessage.setType(MessageType::task1);
        respMessage.setData(m_taskProcessor -> execute(message.getData()).c_str());
        delete m_taskProcessor;
    }
    break;

    case MessageType::task2:
    {
        m_taskProcessor = m_processorFactory.createTaskProcessor(static_cast<int>(MessageType::task2));
        respMessage.setType(MessageType::task2);
        respMessage.setData((m_taskProcessor -> execute(message.getData())).c_str());
        delete m_taskProcessor;        
    }
    break;
    case MessageType::task4: 
    {
        m_taskProcessor = m_processorFactory.createTaskProcessor(static_cast<int>(MessageType::task4));
        respMessage.setType(MessageType::task4);
        respMessage.setData((m_taskProcessor -> execute(message.getData())).c_str());
        delete m_taskProcessor;       
    }
    break;

    default:
        respMessage = "Unsupported message type.\n";
        break;
    }
    return respMessage;
}

