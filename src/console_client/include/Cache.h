
#pragma once

#include <iostream>


class Cache {
 public:
    static Cache &instance();

    std::string getTextData();

    int getTypeData();

    void setTextData(const std::string &text);

    void setTypeData(int type);

    void resetCache();

 private:
    Cache() = default;

    mutable int m_type;

    std::string m_text;
};