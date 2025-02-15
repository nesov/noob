
#pragma once

#include <mutex>
#include "JsonObject.h"


class MessageHandler {
    public:
        JsonObject handle(const JsonObject& message);
            
    private:
        std::mutex m_mtx;
};
    