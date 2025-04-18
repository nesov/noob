
#pragma once

#include "proc/ITaskProcessor.h"
#include "proc/StringParser.h"
#include "proc/ProcConsts.h"

class TaskProcessor_2 : public ITaskProcessor {
 public:
  TaskProcessor_2();
  std::string execute(const std::string &);

 private:
  StringParser m_parser;

  template <typename T>
  T taskTwo(T a, T b) {
    return a + b;
  }
};
