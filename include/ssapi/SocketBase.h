#pragma once

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

#include "ssapi/Message.h"

class SocketBase {
 public:
    SocketBase() = default;
    ~SocketBase() = default;
    void Socket();
    void SetSocketOptions();
    void Bind(int);
    void Listen();
    int Accept();
    void Connect(const char*, int );
    void Send(int , const void*, size_t);
    void Receive(int , void*, size_t);
    void Close();
    void Close(int);
    int getSocket();

    void identifyConnection(int);

    Message receiveMessage(int);
    bool sendMessage(int, const Message& );
 protected:
    int m_socket;
    sockaddr_in m_address;
};