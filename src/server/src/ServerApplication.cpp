
#include "ServerApplication.h"
#include "MessageHandler.h"

ServerApplication::ServerApplication(const int port) {
    lock();
    m_messageHandler = new MessageHandler;
    m_networkService = new TcpSocketServer(port);
    m_networkService -> start();
}

ServerApplication::~ServerApplication() {
    for (auto& worker : m_workers) {
        if (worker.joinable()) {
            worker.join();
        }
        this -> unlock();
    }
    m_networkService -> stop();

    if (m_networkService) {
        delete m_networkService;
        m_networkService = nullptr;
    }
    if (m_messageHandler) {
        delete m_messageHandler;
        m_messageHandler = nullptr;
    }
 }

void ServerApplication::serve(){
    while (true) {
        std::pair<int, Message> itemsToHandle = m_queue.waitAndPop();
        Message responceMessage = m_messageHandler->handle(itemsToHandle.second);
        m_networkService -> sendMessage(itemsToHandle.first, responceMessage);

        std::cout<<"Inc Message : "<< itemsToHandle.second <<std::endl;
        std::cout<<"Out Message : "<< responceMessage <<std::endl;;
    }
}


void ServerApplication::listen(){
    while (true) {
        int connection = m_networkService->Accept();
        Message incomingMessage  = m_networkService -> receiveMessage(connection);
        m_queue.push({connection, incomingMessage});
    }
}

void ServerApplication::run(){
    m_workers.emplace_back([&]() { listen();});
    m_workers.emplace_back([&]() { serve(); }); 

    // for (auto& worker : m_workers) {
    //     if (worker.joinable()) {
    //         worker.join();
    //     }
    // }
}

void ServerApplication::lock() {
    m_lock = open(fileToLock, O_CREAT | O_RDWR, 0666);
    if (m_lock == -1) {
        std::cerr << "Server is already running!\n";
        exit(EXIT_FAILURE);
    }

    if (flock(m_lock, LOCK_EX | LOCK_NB) == -1){
        std::cerr << "Server is already running!\n";
        close(m_lock);
        exit(EXIT_FAILURE);
    }
}

void ServerApplication::unlock() {
    if (m_lock != -1) {
        flock(m_lock, LOCK_UN);
        close(m_lock);
        unlink(fileToLock);
    }
}


