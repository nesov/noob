#pragma once 

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <resolv.h>

#include <iostream>

namespace ssapi{

    struct sockaddr_inn {
        sockaddr_in server_address;
    }; 

    struct Message {
        char type;
        void* data;
    };
}