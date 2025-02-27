
#include "MainDialog.h"


void MainDialog::show() {
    std::cout
    <<"+------------------------------------------------------+\n"
    <<"| "<<"Echo mode - 0                                        |\n"
    <<"| "<<"Task (1)  - 1 Send first name, receive fullname.     |\n"
    <<"| "<<"Task (2) -  2 Send two nums, receive sum of elements.|\n"
    <<"| "<<"Task (4) -  4 Send nums arr, receive Max element.    |\n"
    <<"+------------------------------------------------------+\n"
    <<"| "<<"                                                     |\n"
    <<"+------------------------------------------------------+\n";
}


int  MainDialog::enterType(){
    int choice;
    while (true) {
        std::cout << "Select task to process: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input! Please enter a number." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return choice;
}


std::string MainDialog::enterText(){
    std::string text;
    std::cout << "Enter message text: ";
    getline(std::cin, text);
    return text;
}

