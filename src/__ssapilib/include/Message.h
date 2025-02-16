#pragma once 

#include <string>

class Message {
    public: 
        Message(const char* data);
    private: 
       std::string m_data;
};