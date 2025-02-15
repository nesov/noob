#pragma once

#include "task_algo.h"

namespace calculations {

    class CalcEngine {
        public:
            CalcEngine();
            ~CalcEngine();
    
    };
    

    struct Data {};

    class ITask {
     public: 
        virtual void execute(Data& ) = 0;
        virtual ~ITask() = 0;
    };


    class Task_1 : public ITask {
     public:  
        void execute(Data& ) { 

        }

    };

    class Task_2 : public ITask {
     public:
        void execute(Data& ){
        
        }
    };


}
