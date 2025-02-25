#pragma once

#include "proc/ITaskProcessor.h"
#include <string>

class TaskProcessor_1 : public ITaskProcessor {
public:
  std::string execute(const std::string& data);
private:
  std::string taskOne(const std::string &firstName);
};
