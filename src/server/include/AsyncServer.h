
#pragma once

#include <atomic>
#include "MessageHandler.h"


class AsyncServer {
 public:
    AsyncServer(int port);
    ~AsyncServer(); 
    void start();
   
 private:
   MessageHandler handler;
   int server_socket;
   int port;
   std::atomic<bool> stop_server;

    void setup_server_socket();
    void listen_for_clients();
    void handle_client(int client_socket);
};