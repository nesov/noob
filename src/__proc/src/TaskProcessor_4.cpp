#include "proc/TaskProcessor_4.h"

TaskProcessor_4::TaskProcessor_4():m_parser(kPatternForTask2){}

std::string TaskProcessor_4::execute(const std::string& data) {
     m_parser.parse(data);
     std::vector<std::string> vec = m_parser.getParseResults();
     if (vec.size() < 2 ) return "Array is 2 and more elements \n";
     
     std::vector<double> doubles;
     for (const std::string& str : vec) {
         double value = std::stod(str);
         doubles.push_back(value);
     }
    return std::to_string(taskFour(doubles));
}


