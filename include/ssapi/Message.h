#pragma once 

#include <string>
#include <ostream>

enum class MessageType {
    task1, task2, echo=99
};

class Message {
    public:
        Message() = default;
        // Message(const Message& other) = default;
        // Message(Message&& other) = default;
        Message(const char* data); 

        friend std::ostream& operator<<(std::ostream& os, const Message& msg);
        // friend void operator=(const Message& other);

        MessageType getType() const;
        std::string getData() const;

        void setData(const char* data);
        void setType(MessageType type); 
        size_t size() ;

        void serialize(std::vector<char>& buffer) const;
        static Message deserialize(const std::vector<char>& buffer);
    private:
        MessageType m_messageType;
        std::string m_messageData;
};

    

