
#pragma once
#include "ITaskProcessor.h"

class TaskProcessor_2 : public ITaskProcessor {
 public:  
    Data execute(Data& data);
 private: 
    template<typename T>
    T taskTwo(T a, T b) {
        /*2 Відправити на сервер два числа, знайти їх суму та повернути результат клієнту. */
       return a + b;
    }
};


