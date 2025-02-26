#pragma once

#include "ssapi/Message.h"
#include "proc/ITaskProcessor.h"
#include  "proc/TaskProcessorFactory.h"
#include "IMessageHandler.h"


class MessageHandler : public IMessageHandler {
    public:
        MessageHandler() = default;
        ~MessageHandler();
        Message handle(const Message&);
            
    private:
        ITaskProcessor* m_taskProcessor;
        TaskProcessorFactory m_processorFactory;
};
    