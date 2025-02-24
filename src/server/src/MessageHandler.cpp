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



Message MessageHandler::handle(const Message& message) {

    Message respMessage;
    // Data data, out;
    int type = static_cast<int> (message.getType());

    switch (type) {
        case 0: {
            m_taskProcessor = new TaskProcessor_1;
            std::string inData  = message.getData();
            std::string outData = m_taskProcessor -> execute(inData);
            
            respMessage.setData(outData.c_str());
            respMessage.setType(MessageType::task1);
            delete m_taskProcessor;
            break;
        }

        case 99:
            respMessage = message;
            break;

        default:
            respMessage = "Unsupported message type\n";
            break;
    }
    return respMessage;
}
