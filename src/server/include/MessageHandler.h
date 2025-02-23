#pragma once

#include <mutex>
#include "ssapi/Message.h"
#include "proc/ITaskProcessor.h"


class MessageHandler {
    public:
        explicit MessageHandler() = default;
        ~MessageHandler() = default;
        Message handle(const Message& message);
            
    private:
        ITaskProcessor* m_taskProcessor;
        // std::mutex m_mtx;
};
    