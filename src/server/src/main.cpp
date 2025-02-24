// #include "ServerApplication.h"
// #include "ssapi/INetworkService.h"
#include "ssapi/TcpSocketServer.h"

int main() {
    // ServerApplication application (9090);
    // application.run();

    // INetworkService* service = new TcpSocketServer(8080);

    TcpSocketServer service(8080);
    service.start();
    // service -> stop();

    return 0;
}