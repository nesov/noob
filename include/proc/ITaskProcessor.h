#pragma once

#include "ssapi/Data.h"

class ITaskProcessor {
    public: 
       virtual std::string execute(const std::string& ) = 0;
       virtual ~ITaskProcessor() = default;
   };
