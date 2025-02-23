#pragma once

#include "proc/ITaskProcessor.h"
#include <string>

class TaskProcessor_1 : public ITaskProcessor {
public:
  // Data execute(Data& data);
  std::string execute(std::string& data);
private:
  char *taskOne(const char* name);
};
