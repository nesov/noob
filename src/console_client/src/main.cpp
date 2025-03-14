
#include "ConsoleApplication.h"
#include "consts.h"


int main(){ 
    welcomeScreen("Client " + kVersion);
    ConsoleApplication application;
    return application.run();
}
