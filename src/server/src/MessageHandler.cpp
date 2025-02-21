#include <string>
#include <iostream>

#include "MessageHandler.h"
#include "ssapi/Message.h"

#include "proc/TaskProcessor_1.h"



Message MessageHandler::handle(const Message& message) {
    std::lock_guard<std::mutex> lock(m_mtx);
    Message respMessage;
    Data data, out;

    switch (message.getType()) {
        case MessageType::task1: {
            std::unique_ptr<ITaskProcessor> taskProcessor = std::make_unique<TaskProcessor_1>();
            data.StringData = message.getData();
            out = taskProcessor->execute(data);
            respMessage.setData(out.StringData.c_str());
            respMessage.setType(MessageType::task1);
            break;
        }

        case MessageType::echo:
            respMessage = message;
            break;

        default:
            std::cerr << "Unsupported message type\n";
            respMessage = "Unsupported message type\n";

            break;
    }
    return respMessage;
}
