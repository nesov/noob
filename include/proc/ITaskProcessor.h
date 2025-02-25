#pragma once

#include <string>

class ITaskProcessor {
 public: 
   virtual std::string execute(const std::string& ) = 0;
   virtual ~ITaskProcessor() = default;
};
