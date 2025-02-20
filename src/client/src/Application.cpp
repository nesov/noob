#include "Application.h"
#include "MainViewController.h"
#include "ssapi/TcpClient.h"
#include "ssapi/Consts.h"

    Application::Application (){
        m_mainViewController = new MainViewController;
        m_networkService = new ssapi::TcpClient(ssapi::kHost,ssapi::kPort);
    }

    Application::~Application (){
        delete m_mainViewController;
        delete m_networkService;
    }

    int Application::run(){
        return Fl::run();      
    }
