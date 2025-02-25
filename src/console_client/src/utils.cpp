#include "utils.h"
#include <iostream>


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

/**
    "+-+  +-+ +------+ +------+ +-----\" <<   <<;
    "|  \ | | | +--+ | | +--+ | | +--+ |"   <<
    "|   \| | | |  | | | |  | | | +--+/"    <<
    "| |\   | | |  | | | |  | | | +--+\ "   <<
    "| | \  | | +--+ | | +--+ | | +--+ |"   <<
    "+-+  +-+ +------+ +------+  +----/"     <<
    Terminal TCP Client 
    Coded by Niesov Oleksandr
    */

