#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <future>
#include <map>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <atomic>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

#include "AsyncServer.h"

AsyncServer::AsyncServer(int port) : port(port), stop_server(false) {}

void AsyncServer::start() {
    setup_server_socket();
    listen_for_clients();
}

AsyncServer::~AsyncServer() {
    stop_server.store(true);
    shutdown(server_socket, SHUT_RDWR);
    close(server_socket);
}

void AsyncServer::setup_server_socket() {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(-1);
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(-1);
    }

    if (listen(server_socket, 10) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(-1);
    }

    std::cout << "Server listening on port " << port << std::endl;
}

void AsyncServer::listen_for_clients() {
    while (!stop_server.load()) {
        sockaddr_in client_addr{};
        socklen_t addr_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0)
        {
            if (stop_server.load())
                return;
            perror("Accept failed");
            continue;
        }
        std::future<void> future = std::async(std::launch::async, [this, client_socket]()
                                              { handle_client(client_socket); });
    }
}

void AsyncServer::handle_client(int client_socket) {
    char buffer[1024];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        try {
            JsonObject message = JsonObject::deserialize(buffer);
            JsonObject response = handler.handle(message);
            std::string response_str = response.serialize();
            send(client_socket, response_str.c_str(), response_str.length(), 0);
        } catch (const std::exception &e) {
            std::cerr << "Error processing request: " << e.what() << std::endl;
        }
    }
    close(client_socket);
}
