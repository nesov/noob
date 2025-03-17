#pragma once

#include "ssapi/INetworkService.h"

#include "IViewController.h"

class Application {
 public:
    Application();
    ~Application();
    static int run();

 private:
    IViewController* m_mainViewController;
    INetworkService* m_networkService;
};

