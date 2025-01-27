#include <iostream>

#include "mainheader.h"

void c_method(){
    std::cout << "Hello from executable" << std::endl;
}

int main(){
    framework_functiona();
    framework_functionb();

    c_method();
    a_method(); 
    b_method();

    return 0;
}
