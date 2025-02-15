#include <string>

#include "MessageHandler.h"
#include "JsonObject.h"


JsonObject MessageHandler::handle(const JsonObject& message) {
    
    std::lock_guard<std::mutex> lock(m_mtx);
    JsonObject response;
    try {
        std::string content = message.get("content");

        if (content == "Task1") {
            int a = std::stoi(message.get("a"));
            int b = std::stoi(message.get("b"));
            response.set("content", "Result: " + std::to_string(a + b));
        } else if (content == "Task2") {
            std::string text = message.get("text");
            std::transform(text.begin(), text.end(), text.begin(), ::toupper);
            response.set("content", text);
        } else {
            response.set("content", "Unknown task.");
        }
    } catch (const std::exception& e) {
        response.set("content", "Error: " + std::string(e.what()));
    }
    return response;
}