
#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

#include <ssapi/INetworkService.h>
#include <ssapi/NetworkServiceFactory.h>
#include <ssapi/Message.h>

#include "BaseDialog.h"

class ConsoleApplication {
public:
    ConsoleApplication();
    ~ConsoleApplication();
    int run();

private:
    bool composeMessageAndSend(int task, std::string &text);
    INetworkService *m_network;
    std::vector<IDialog *> m_dialogs;
    NetworkServiceFactory m_netFactory;
};