#pragma once
#include "ssapi/Message.h"

class INetwork {
    public: 
        virtual ~INetwork();
        virtual void start() = 0;
        virtual void stop() = 0;

        virtual void sendMessage(const Message&) = 0;
        virtual Message receiveMessage() = 0;
};