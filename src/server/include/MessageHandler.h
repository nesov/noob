#pragma once

#include <mutex>
#include "ssapi/Message.h"
#include "proc/ITaskProcessor.h"


class MessageHandler {
    public:
        MessageHandler() = default;
        ~MessageHandler();
        Message handle(const Message& message);
            
    private:
        ITaskProcessor* m_taskProcessor;
        // std::mutex m_mtx;
};
    