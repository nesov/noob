#include "Application.h"
#include "MainViewController.h"

#include "ssapi/NetworkServiceFactory.h"
#include "consts.h"

    Application::Application (){
        m_networkService = (new NetworkServiceFactory) -> createNetworkService(true, kHost, kPort);
        m_mainViewController = new MainViewController(m_networkService);
    }

    Application::~Application (){
        delete m_mainViewController;
        delete m_networkService;
    }

    int Application::run(){
        return Fl::run();      
    }
