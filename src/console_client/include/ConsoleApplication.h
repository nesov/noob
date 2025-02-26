

#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <ssapi/INetworkService.h>
#include <ssapi/NetworkServiceFactory.h>
#include <ssapi/Message.h>

class ConsoleApplication {
 public: 
    ConsoleApplication() = default;
    ~ConsoleApplication();

    void run();

private:
    void clearScreen();
    int selectTaskDialog();
    std::string enterTextDialog();
    bool composeMessageAndSend(int task, std::string &text);
    bool claerScreenDialog();
    void show(const Message& sent, const Message& received);
    void show(const std::string& sent, const std::string& received);

    INetworkService* m_network;

};