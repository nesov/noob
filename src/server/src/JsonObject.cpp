#include <sstream>
#include <string>

#include "JsonObject.h"

void JsonObject::set(const std::string &key, const std::string &value) {
    data[key] = value;
}

std::string JsonObject::get(const std::string &key) const {
    auto it = data.find(key);
    if (it != data.end()) {
        return it->second;
    }
    throw std::runtime_error("Key not found");
}

std::string JsonObject::serialize() const {
    std::ostringstream oss;
    oss << "{";
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (it != data.begin())
            oss << ",";
        oss << "\"" << it->first << "\":\"" << it->second << "\"";
    }
    oss << "}";
    return oss.str();
}

JsonObject JsonObject::deserialize(const std::string &str) {
    JsonObject jsonObject;
    size_t start = 0, end = 0;
    while ((start = str.find("\"", end)) != std::string::npos) {
        end = str.find("\"", start + 1);
        std::string key = str.substr(start + 1, end - start - 1);

        start = str.find("\"", end + 1);
        end = str.find("\"", start + 1);
        
        std::string value = str.substr(start + 1, end - start - 1);
        jsonObject.set(key, value);
    }
    return jsonObject;
}
