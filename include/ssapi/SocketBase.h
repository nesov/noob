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
   void Bind(int port);
   void Listen();
   int Accept();
   bool Connect(const char * host, int port);
   void Send(int socket, const void* data, size_t size);
   void Receive(int socket, void * data, size_t size);
   void Close();
   void Close(int socket);
   int getSocket();
   void identifyConnection(int socket);
   bool isConnected();
   Message receiveMessage(int socket);
   bool sendMessage(int socket, const Message& mssage);

protected:
   int m_socket;
   sockaddr_in m_address;
};
