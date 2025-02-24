
#include "ServerApplication.h"

ServerApplication::ServerApplication(const int port) {
    m_networkService = new TcpServerSocket(port);
}


ServerApplication::~ServerApplication() {
    for (auto& worker : m_workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
    if (m_networkService) delete m_networkService;
}


void ServerApplication::serve(){
    while (true) {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_condition.wait(lock, [this]() { return !m_incomingMessages.empty(); });

        int client = m_incomingMessages.front().first;
        Message inMessage = m_incomingMessages.front().second;

        m_incomingMessages.pop();

        lock.unlock();

        m_messageHandler = new MessageHandler;
        Message outMessage = m_messageHandler -> handle(inMessage);
        m_networkService -> sendMessage(client, outMessage);
        delete m_messageHandler;
    }
}


void ServerApplication::listen(){
    while (true) {
        m_networkService -> listenAndAcceptConnections(m_incomingMessages);
        // int connection = m_networkService -> acceptConnection();
        // Message incomingMessage = m_networkService -> receiveMessage(connection);
        {
            std::lock_guard<std::mutex> lock(m_mtx);
            // m_incomingMessages.emplace(connection, incomingMessage);
        }
        m_condition.notify_one();
    }
}

void ServerApplication::run(){
    m_workers.emplace_back([&]() { listen();}).detach();
    m_workers.emplace_back([&]() { serve(); }).detach(); 
}





// void ServerApplication::lock(){
//     int lockFile = open ("/tmp/server.lock", O_CREAT | O_RDWR, 0666);
//     if (lockFile == -1) {
//         std::cerr << "openr";
//         // return 1;
//     }

//     if (flock(lockFile, LOCK_EX | LOCK_NB) == -1) {
//         std::cerr << "Программа уже запущена!\n";
//         close(lockFile);
//         // return 1;
//     }


    
// }

// Message ServerApplication::customHandler(const Message& messageIn) {
//     Message messageOut = m_messageHandler -> handle(messageIn);
//     return messageOut;
// }




