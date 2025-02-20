#pragma once
#include "ssapi/Message.h"

class INetworkService {
 public:
    virtual ~INetworkService();
        
    virtual bool start() = 0;
    virtual void stop() = 0;
        
    virtual bool sendMessage(const Message& message) = 0;
    virtual Message receiveMessage() = 0;
};

    