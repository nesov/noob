#pragma once 

#include <iostream>
#include <string>

//Server
constexpr const char* fileToLock = {"/tmp/tcp_server.lock"};

//Common
constexpr std::string  kHost {"127.0.0.1"};
constexpr int kPort {8080};

constexpr std::string kVersion {"v1.2.13"};

inline void welcomeScreen(const std::string& who) {
    std::cout << std::endl
        << "+-+  +-+ +------+ +------+ +-----\" \n"
        << "|  \\ | | | +--+ | | +--+ | | +--+ |\n"
        << "|   \\| | | |  | | | |  | | | +--+/ \n"
        << "| |\\   | | |  | | | |  | | | +--+\\ \n"
        << "| | \\  | | +--+ | | +--+ | | +--+ |\n"
        << "+-+  +-+ +------+ +------+  +----/ \n"
        << std::endl;

    std::cout << "Terminal TCP "<< who <<"\n"
              << "Coded by Niesov Oleksandr \n"
              << std::endl;
}
