
#pragma once 

#include "proc/ITaskProcessor.h"
#include "proc/StringParser.h"
#include "proc/ProcConsts.h"

class TaskProcessor_4 : public ITaskProcessor {
 public:  
   TaskProcessor_4();
   std::string execute(const std::string&);

 private: 
   StringParser m_parser;

   template <typename T>
   T taskFour(std::vector<T>& arr) {
      T max = *std::max_element(arr.begin(),arr.end());
      return max;
  }
};
