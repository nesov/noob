
#include <string>
#include "proc/TaskProcessor_1.h"
#include "proc/ProcConsts.h"

TaskProcessor_1::TaskProcessor_1() : m_parser(kPatternForTask1){}

std::string TaskProcessor_1::execute(const std::string& data) {
    return taskOne(data);
}

std::string TaskProcessor_1::taskOne(const std::string& firstName){
    std::string predicate {"Oleksandr"};
    return (firstName == predicate) ? predicate + " Niesov" : "To make it work as expected, you need to send -> Oleksandr";
}

