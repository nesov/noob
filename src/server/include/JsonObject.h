#pragma once

#include <string>
#include <map>

class JsonObject {
public:
    void set(const std::string &key, const std::string &value);
    std::string get(const std::string &key) const;

    std::string serialize() const;
    static JsonObject deserialize(const std::string &str);

private:
    std::map<std::string, std::string> data;
};