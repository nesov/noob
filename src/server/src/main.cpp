
#include "ServerApplication.h"


int main() {
    welcomeScreen("Async Server v1.2.11");
    ServerApplication application(8080);
    application.run();
    return 0; 
}
