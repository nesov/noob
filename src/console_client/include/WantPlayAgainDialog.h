
#pragma once

#include "BaseDialog.h"
#include <iostream>



class WantPlayAgainDialog : public BaseDialog {
    public:
        WantPlayAgainDialog() = default;
        ~WantPlayAgainDialog() = default;
        void show() override;
        bool yesNo();
};
