#pragma once

#include "task_algo.h"

namespace calculations {

    struct Data {
        void* getVal();
        void* data;
    };

    class ITask {
     public: 
        virtual void execute(Data& ) = 0;
        virtual ~ITask() = 0;
    };


    class Task_1 : public ITask {
     public:  
        void execute(Data& data) { 
            const char* prepdata = static_cast<char*>(data.getVal());
            const char* resltData = taskOne(prepdata); // result data;
        }
     private: 
        char* taskOne(const char* name){
            /*
            1 Відправити з клієнта на сервер своє ім’я,
            на сервері додати до імені своє прізвище та відпрарезультат на клієнт.
            */
            static char result[20] = ""; 
            const char* firstName = "Alexandr";
            
            if (strcmp(name, firstName) == 0) {
                strcpy(result, firstName);  
                strcat(result, " Niesov"); 
                return result;
            }
            return result;
        }
    };

}
