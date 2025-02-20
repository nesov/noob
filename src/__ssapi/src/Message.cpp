
#include "ssapi/Message.h"

// Message::Message() {}

Message::Message(std::string data) : m_messageData(std::move(data)) {}

Message::Message(const char *data) : m_messageData(data) {}

Message::Message(Message&& other){
    std::swap (this->m_messageData, other.m_messageData);
    std::swap (this->m_messageType, other.m_messageType);
}

// Message::~Message(){}

std::string Message::getData() const { 
    return m_messageData; 
}

MessageType Message::getType() const { 
    return m_messageType; 
}

size_t Message::size() const {
    return m_messageData.size(); 
}

std::vector<char> Message::toBuffer() const {
    uint32_t dataSize = htonl(static_cast<uint32_t>(m_messageData.size()));
    std::vector<char> buffer(sizeof(dataSize) + m_messageData.size());
    std::memcpy(buffer.data(), &dataSize, sizeof(dataSize));
    std::memcpy(buffer.data() + sizeof(dataSize), m_messageData.data(), m_messageData.size());
    return buffer;
}

inline static Message fromBuffer(const std::vector<char> &buffer) {
    if (buffer.size() < sizeof(uint32_t)) {
        throw std::runtime_error("Invalid buffer size");
    }
    uint32_t dataSize;
    std::memcpy(&dataSize, buffer.data(), sizeof(dataSize));
    dataSize = ntohl(dataSize);
    if (buffer.size() < sizeof(uint32_t) + dataSize) {
        throw std::runtime_error("Incomplete message");
    }
    return Message(std::string(buffer.begin() + sizeof(uint32_t), buffer.begin() + sizeof(uint32_t) + dataSize));
}
