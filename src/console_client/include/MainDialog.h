
#pragma once

#include <iostream>
#include <string>
#include <ios>
#include <limits>


#include "BaseDialog.h"

class MainDialog : public BaseDialog {
 public:
    MainDialog() = default;
    ~MainDialog() = default;
    void show() override;
    
    int enterType();
    std::string enterText();
};
