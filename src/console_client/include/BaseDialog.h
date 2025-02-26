
#pragma once 

#include <cstdlib>
#include "IDialog.h"


class BaseDialog : public IDialog {
    public:
        virtual ~BaseDialog() = default;
        virtual void show() = 0;

    protected:
        void clearScreen();
};