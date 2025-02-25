#pragma once

#include <string>

#include "proc/ITaskProcessor.h"
#include "proc/StringParser.h"
#include "proc/ProcConsts.h"


class TaskProcessor_1 : public ITaskProcessor {
public:
  TaskProcessor_1();
  std::string execute(const std::string& data);

private:
  std::string taskOne(const std::string &firstName);
  StringParser m_parser;
};
