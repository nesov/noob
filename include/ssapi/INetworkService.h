#pragma once

#include "ssapi/Message.h"

class INetworkService {
 public:
    virtual ~INetworkService() = default;

    virtual bool start() = 0;
    virtual void stop() = 0;

    virtual bool sendMessage(const Message& message) = 0 ;
    virtual bool sendMessage(int socket, const Message &message) = 0;

    virtual Message receiveMessage() = 0;
    virtual Message receiveMessage(int socket) = 0 ;

    virtual bool isConnected() = 0; //prothesis for client
    
    virtual int Accept() = 0; //prothesis for server 
};

    