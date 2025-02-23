#pragma once

#include "IViewController.h"

#include "ssapi/INetwork.h"

class Application {
    public:
        Application();
        ~Application();

        static int run();
    private:
        IViewController* m_mainViewController;
        INetwork* m_networkService;
};
