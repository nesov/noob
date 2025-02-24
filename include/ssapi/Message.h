#pragma once 

#include <string>
#include <ostream>

enum class MessageType : uint8_t{
    task1, task2, echo=99
};

class Message {
    public:
        Message() = default;
        Message(const Message& other) = default;
        Message(Message&& other) = default;
        Message(const char* data); 
        Message(std::string& );
        Message(MessageType type, const std::string& data);



        friend std::ostream& operator<<(std::ostream& os, const Message& msg);
        Message& operator=(const Message& other) = default;

        MessageType getType() const;
        std::string getData() const;

        void setData(const char* data);
        void setType(MessageType type); 
        size_t size();

        void serialize(std::vector<char>& buffer) const;
        static Message deserialize(const std::vector<char>& buffer);

        static void toBytes(const Message&, char*  );
        static void fromBytes(const char*, Message& ); 
        

    private:
        MessageType m_messageType;
        std::string m_messageData;
};




// class Message {
// public:
//     MessageType type;
//     std::string data;

//     Message(MessageType t, const std::string& d) : type(t), data(d) {}
// };
    

