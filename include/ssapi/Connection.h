
#pragma once

struct Connection {
    int clientSocket;

    // bool operator==(Connection& other) const {
    //     return this->clientSocket == other.clientSocket;
    // }

    bool operator==(int socket) const {
        return clientSocket == socket;
    }
};
