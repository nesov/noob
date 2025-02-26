
#include "ssapi/Message.h"


Message::Message(const char* data) : 
                m_messageType(MessageType::echo), m_messageData(std::string(data)) {}

  
std::ostream& operator<<(std::ostream &os, const Message& message) {
    os <<static_cast<int>(message.m_messageType) << " : " << message.m_messageData;
    return os;
}


Message::Message(MessageType type, const std::string& data) : m_messageType(type), m_messageData(data) {}


Message::Message(std::string& data) : m_messageType(MessageType::echo), m_messageData(data) {}


MessageType Message::getType() const {
    return m_messageType;
}


std::string Message::getData() const {
    return m_messageData;
}


void Message::setData(const char* data) {
    m_messageData = std::string(data);
}


void Message::setData(std::string& data) {
    m_messageData = data;
}


void Message::setType(MessageType type) {
    m_messageType = type;
}


size_t Message::size() {
    return sizeof(m_messageType) + m_messageData.size();
}


void Message::serialize(std::vector<char>& buffer) const {
    buffer.push_back(static_cast<char>(m_messageType));
    buffer.insert(buffer.end(), m_messageData.begin(), m_messageData.end());
}


Message Message::deserialize(const std::vector<char>& buffer) {
    Message message;
    message.m_messageType = static_cast<MessageType>(buffer[0]);
    message.m_messageData = std::string(buffer.begin() + 1, buffer.end());
    return message;
}


void Message::toBytes(const Message& message, char* bytes){
    std::memcpy(bytes, &message, sizeof(message));
}


void Message::fromBytes(const char* bytes, Message& message) {
    std::memcpy(&message, bytes, sizeof(message));
} 