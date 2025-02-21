#pragma once

#include "MessageHandler.h"
#include "ssapi/INetworkService.h"
#include "ssapi/Message.h"

#include <memory>

class ServerApplication {
 public:
    ServerApplication(int port);
    ~ServerApplication();
    void serve();

 private:
    // std::unique_ptr<MessageHandler*> m_messagehandler;
    // std::unique_ptr<INetworkService*> m_networkService;

    MessageHandler* m_messagehandler;
    INetworkService* m_networkService;
};
