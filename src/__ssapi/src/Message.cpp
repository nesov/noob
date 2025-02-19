
#include <sstream>
#include <variant>

#include "ssapi/Message.h"

Message::Message(MessageType type, const Data& data) 
            : m_messageType(type), m_messageData(data) {}

Message::Message(char* data) {
    m_messageType = MessageType::StringData;
    m_messageData.StringData = data;
}

// Message::Message(char type, int data) :m_type(type){
//     m_messageData.IntegerData = data;
// }

Message::Message() { };

Message::Message(int data) {
    m_messageType = MessageType::IntegerData;
    m_messageData.IntegerData = data;
}
Message::Message(bool data) {
    m_messageType = MessageType::BoolData;
    m_messageData.BoolData = data;
}

Message::~Message(){};

// std::string Message::getData() {
//     return m_data;
// }

Data Message::getData() {
    return m_messageData;
}


std::string Message::toBuffer() {
    std::ostringstream oss;
    oss << static_cast<int>(m_messageType) << " " 
        << m_messageData.IntegerData << " " 
        << m_messageData.BoolData << " " 
        << m_messageData.StringData;
    return oss.str();
}

Message Message::fromBuffer(const std::string& buffer) {
    std::istringstream iss(buffer);
    int type;
    Data data;
    iss >> type >> data.IntegerData >> data.BoolData;
    std::getline(iss, data.StringData);
    
    return Message(static_cast<MessageType>(type), data);
}




