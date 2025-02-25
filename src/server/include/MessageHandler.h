#pragma once

#include "ssapi/Message.h"
#include "proc/ITaskProcessor.h"


class MessageHandler {
    public:
        MessageHandler() = default;
        ~MessageHandler();
        Message handle(const Message&);
            
    private:
        Message convert(const Message&, const ITaskProcessor&);
        ITaskProcessor* m_taskProcessor;
};
    