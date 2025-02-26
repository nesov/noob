

#include "WantPlayAgainDialog.h"

void WantPlayAgainDialog::show() {
    std::cout << "Want to play again Y/n : "; 
}

bool WantPlayAgainDialog::yesNo() {
    char choice;
    std::cin >> choice;
    std::cin.ignore();
    
    switch (choice){
        case 'Y':
            BaseDialog::clearScreen();
            return true;
        case 'n':
            return false;
        default:
            return false;
    }
}
