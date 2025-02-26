
#pragma once

#include "BaseDialog.h"
#include <iostream>
#include <string>

class MainDialog : public BaseDialog {
    public:
        MainDialog() = default;
        ~MainDialog() = default;

        void show() override;
        int enterType();
        std::string enterText();
};
