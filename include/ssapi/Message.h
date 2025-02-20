#pragma once 

#include <vector>
#include <string>

enum class MessageType {
    IntegerData, BoolData, StringData
};

class Message {
    public:
        Message() = default;
        Message(std::string data);
        Message(const char* data);
        Message(Message&&);
        ~Message() = default;

        std::string getData() const;
        MessageType getType() const;
        size_t size() const;
    
        std::vector<char> toBuffer() const;
        static Message fromBuffer(const std::vector<char>& buffer) ;
    
    private:
        MessageType m_messageType;
        std::string m_messageData;
    };
