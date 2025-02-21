#pragma once

#include "proc/ITaskProcessor.h"

class TaskProcessor_1 : public ITaskProcessor {
public:
  Data execute(Data& data);
private:
  char *taskOne(const char* name);
};
