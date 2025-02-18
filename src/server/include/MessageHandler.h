
#pragma once

#include <mutex>
#include "JsonObject.h"
#include "Message.h"
#include "ITaskProcessor.h"


class MessageHandler {
    public:
        JsonObject handle(const JsonObject& message);
        Message    handle(const Message& message);
            
    private:
        ITaskProcessor* taskProcessor;
        std::mutex m_mtx;
};
    