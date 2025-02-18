#pragma once 

#include "ssapi/Data.h"


enum class MessageType {
    IntegerData, BoolData, StringData
};

class Message {
 public: 
    Message() = default;
    Message(char* data);
    Message(int data);
    Message(bool data);

    ~Message();
    
    Data getData();
    MessageType getType();

    std::string toBuffer() const;
    static Message fromBuffer(const std::string& buffer);
    
 private: 
    MessageType m_messageType;
    Data m_messageData;   
};
