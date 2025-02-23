#include "ServerApplication.h"

int main() {
    ServerApplication application (8080);
    application.run();
    return 0;
}
