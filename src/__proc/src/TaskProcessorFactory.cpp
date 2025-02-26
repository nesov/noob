
#include "proc/TaskProcessorFactory.h"

ITaskProcessor *TaskProcessorFactory::createTaskProcessor(int type) {
    switch (type) {

    case 1:
        return new TaskProcessor_1();

    case 2:
        return new TaskProcessor_2();
        
    case 3:
    case 4:
        return new TaskProcessor_4();
        break;

    default:
        std::cerr << "Unknown task to do\n";
        return nullptr;
    }
}
