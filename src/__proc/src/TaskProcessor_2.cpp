
#include "proc/TaskProcessor_2.h"

TaskProcessor_2::TaskProcessor_2():m_parser(kPatternForTask2){}

std::string TaskProcessor_2::execute(const std::string& data){
     m_parser.parse(data);
     std::vector<std::string> vec = m_parser.getParseResults();
     if (vec.size() < 2 ) return "There should be at least two numbers in this string\n";
     double a = std::stod(vec[0]);
     double b = std::stod(vec[1]);
     return "The Sum (first two found numbers) is: " + std::to_string(taskTwo(a,b));
}
