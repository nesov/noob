
#include <iostream>

#include "BaseDialog.h"


class WantPlayAgainDialog : public BaseDialog {
    public:
        WantPlayAgainDialog() = default;
        ~WantPlayAgainDialog() = default;
        void show() override;
        bool yesNo();
};
