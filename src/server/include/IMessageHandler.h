#pragma once 

#include "ssapi/Message.h"

class IMessageHandler {
    public:
        virtual ~IMessageHandler() = default;
        virtual Message handle(const Message&) = 0;
};
    