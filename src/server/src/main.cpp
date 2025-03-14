
#include "ServerApplication.h"
#include "consts.h"


int main() {
    welcomeScreen("Async Server " + kVersion);
    ServerApplication application(kPort);
    application.run();
    return 0; 
}
