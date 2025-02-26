#include "ServerApplication.h"
#include "consts.h"


int main() {
    welcomeScreen("Async Server v1.2.1");
    ServerApplication application(8080);
    application.run();
    return 0; 
}
