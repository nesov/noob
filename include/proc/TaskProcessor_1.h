#pragma once

#include "proc/ITaskProcessor.h"
#include <string>

class TaskProcessor_1 : public ITaskProcessor {
public:
  std::string execute(const std::string& data);
private:
  // char *taskOne(const char* name);
  std::string taskOne(const std::string &firstName);
};
