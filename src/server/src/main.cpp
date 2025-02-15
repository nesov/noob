
#include "AsyncServer.h"

int main() {
    AsyncServer server(8080);
    server.start();
    return 0;
}
