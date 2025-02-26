#include "ServerApplication.h"
#include "consts.h"


int main() {
    welcomeScreen("Async Server");
    ServerApplication application(8080);
    application.run();
    return 0; 
}
