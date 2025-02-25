#pragma once

#include "ssapi/Message.h"

class INetworkService {
 public:
    virtual ~INetworkService() = default;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual bool sendMessage(const Message& message) = 0 ;
    virtual bool sendMessage(int socket, const Message &message) = 0;

    virtual Message receiveMessage() = 0;
    virtual Message receiveMessage(int socket) = 0 ;
    
    virtual int Accept() = 0;
};

    