#include "ServerApplication.h"

int main() {
    ServerApplication application(8080);
    application.serve();
    return 0;
}
