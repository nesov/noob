#pragma once

#include "ssapi/Message.h"
#include "proc/ITaskProcessor.h"
#include "IMessageHandler.h"


class MessageHandler : public IMessageHandler {
    public:
        MessageHandler() = default;
        ~MessageHandler();
        Message handle(const Message&);
            
    private:
        // Message convert(const Message&, const ITaskProcessor&);
        ITaskProcessor* m_taskProcessor;
};
    