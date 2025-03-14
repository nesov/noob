
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

    bool iSsupportedMessageType = (message.getType() == MessageType::task1) 
                            ||  (message.getType() == MessageType::task2) 
                            ||  (message.getType() == MessageType::task4);
                    
    if (iSsupportedMessageType){
        m_taskProcessor = m_processorFactory.createTaskProcessor(static_cast<int>(message.getType()));
        respMessage.setType(message.getType());
        respMessage.setData(m_taskProcessor -> execute(message.getData()).c_str());
        delete m_taskProcessor;

    } else if(message.getType() == MessageType::echo){
        respMessage = message;
        
    } else {
        respMessage.setType(message.getType());
        respMessage.setData("Unsupported message type.\n");
    }
    return respMessage;
}
