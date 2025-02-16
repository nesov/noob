#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <resolv.h>

#include <iostream>

struct sockaddr_inn {
    sockaddr_in server_address;
};
