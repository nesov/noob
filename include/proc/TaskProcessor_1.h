#pragma once

#include "proc/ITaskProcessor.h"
#include "proc/StringParser.h"

#include <string>

class TaskProcessor_1 : public ITaskProcessor {
public:
  TaskProcessor_1();
  std::string execute(const std::string& data);
private:
  std::string taskOne(const std::string &firstName);
  StringParser m_parser;
};
