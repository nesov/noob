#pragma once 


class IDialog {
    public:
        virtual ~IDialog() = default;
        virtual void show() = 0;
};