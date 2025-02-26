#pragma once 

#include <iostream>

#include "proc/TaskProcessor_1.h"
#include "proc/TaskProcessor_2.h"
#include "proc/TaskProcessor_4.h"

#include "ITaskProcessor.h"

class TaskProcessorFactory {
    public:
        TaskProcessorFactory() = default;
        ~TaskProcessorFactory() = default;
        ITaskProcessor* createTaskProcessor(int);
};