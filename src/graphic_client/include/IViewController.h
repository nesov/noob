#pragma once 

class IViewController {
    public:
        virtual ~IViewController() = 0;
        virtual void Draw() = 0;
};
