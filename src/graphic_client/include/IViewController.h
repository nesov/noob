#pragma once 


class IViewController {
 public:
    virtual ~IViewController() = default;
    virtual void Draw() = 0;
};
