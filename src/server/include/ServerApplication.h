// #pragma once

// #include <thread>
// #include <vector>
// #include <queue>

// #include "MessageHandler.h"
// #include "ssapi/INetworkService.h"
// #include "ssapi/Message.h"
// #include "TcpServerSocket.h"

// class ServerApplication {
//     using MessagesQueue = std::queue<std::pair<int, Message>>;
//     using Workers       = std::vector<std::thread>;

//  public:
//     ServerApplication(int port);
//     ~ServerApplication();
//     void run();

// private:

//     void listen();
//     void serve();
//     // void listen(MessagesQueue& );
//     // void serve (MessagesQueue& );

//     // void lock();
//     // void unlock();

//     MessagesQueue       m_incomingMessages;
//     // std::queue<std::pair<int, Message>>& m_incomingMessages;

//     MessageHandler*     m_messageHandler;
//     TcpServerSocket*    m_networkService;
//     Workers             m_workers;


//     std::mutex m_mtx;
//     std::condition_variable m_condition;
// };
