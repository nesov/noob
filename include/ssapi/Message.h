#pragma once 

#include <string>
#include <ostream>


enum class MessageType : uint8_t {
    echo, task1, task2, task4 = 4 
};


class Message {
    public:
        Message() = default;
        Message(const Message& other) = default;
        Message(Message&& other) = default;
        
        Message(const char* data); 
        Message(std::string& );
        Message(MessageType type, const std::string& data);

        MessageType getType() const;
        std::string getData() const;

        void setData(const char* data);
        void setData(std::string& data);
        void setType(MessageType type); 
        size_t size();

        void serialize(std::vector<char>& buffer) const;
        static Message deserialize(const std::vector<char>& buffer);

        static void toBytes(const Message&, char*  );
        static void fromBytes(const char*, Message& ); 

        friend std::ostream& operator<<(std::ostream& os, const Message& msg);
        Message& operator=(const Message& other) = default;
        
    private:
        MessageType m_messageType;
        std::string m_messageData;

};
