#include "Application.h"
#include "MainViewController.h"

#include "ssapi/NetworkServiceFactory.h"
#include "consts.h"


Application::Application (){
    m_networkService = m_netServiceFactory.createNetworkService(true, kHost, kPort);
    m_mainViewController = new MainViewController(m_networkService);
}


Application::~Application (){
    if (m_mainViewController){
        delete m_mainViewController;
        m_mainViewController = nullptr;
    }
    if (m_networkService){
        delete m_networkService;
        m_networkService = nullptr;
    }
}


int Application::run(){
    return Fl::run();      
}
