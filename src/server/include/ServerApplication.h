#pragma once

#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>

#include <vector>
#include <iostream>
#include <thread>

#include "ssapi/INetworkService.h"
#include "ssapi/TcpSocketServer.h"
#include "ssapi/Message.h"

#include "MessageHandler.h"
#include "MessageQueue.h"
#include "ServerConsts.h"




class ServerApplication {
 public:
    ServerApplication(int port);
    ~ServerApplication();
    void run();

 private:
    void listen();
    void serve();

    void lock();
    void unlock();

    MessageHandler*     m_messageHandler;
    INetworkService*    m_networkService;
    MessageQueue<std::pair<int, Message> > m_queue;
    std::vector <std::thread> m_workers;
    int m_lock;
};
