#include "Application.h"
#include "MainViewController.h"

    Application::Application (){
        m_mainViewController = new MainViewController;
    }

    Application::~Application (){
        delete m_mainViewController;
    }

    int Application::run(){
        return Fl::run();      
    }
