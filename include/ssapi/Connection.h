
#pragma once

struct Connection {
    int clientSocket;
    bool operator==(int socket) const {
        return clientSocket == socket;
    }
};
