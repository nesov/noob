#pragma once

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

class SocketBase {
public:
    SocketBase();
    ~SocketBase();
    void Socket();
    void SetSocketOptions();
    void Bind(int);
    void Listen();
    int Accept();
    void Connect(const char *host, int port);
    void Send(int socket, const char *data, size_t);
    void Receive(int socket, char *data, size_t);
    void Close();
    void Close(int);

    int getSocket();
protected:
    int m_socket;
    sockaddr_in m_address;
};