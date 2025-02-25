#include "ServerApplication.h"

void welcomeScreen(const char* who) {
    std::cout << std::endl
        << "+-+  +-+ +------+ +------+ +-----\" \n"
        << "|  \\ | | | +--+ | | +--+ | | +--+ |\n"
        << "|   \\| | | |  | | | |  | | | +--+/ \n"
        << "| |\\   | | |  | | | |  | | | +--+\\ \n"
        << "| | \\  | | +--+ | | +--+ | | +--+ |\n"
        << "+-+  +-+ +------+ +------+  +----/ \n"
        << std::endl;

    std::cout << "Terminal TCP "<< who <<"\n"
              << "Coded by Niesov Oleksandr \n"
              << std::endl;
}

int main() {
    welcomeScreen("Async Server");
    ServerApplication application(8080);
    application.run();
    return 0; 
}
