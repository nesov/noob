
#include <string>
#include "proc/TaskProcessor_1.h"

std::string TaskProcessor_1::execute(const std::string& data) {
    return taskOne(data);
}

std::string TaskProcessor_1::taskOne(const std::string& firstName){
    std::string predicate {"Alexandr"};
    return (firstName == predicate ) ? predicate + " Niesov" : "NO MATCH";
}

 //BUG: 
    /*
        1. send Alexandr
        2. recieve Alexandr Niesov  - which is correct behaviour
        3. send something other, like 111 for example 
        AR: 
            - recieve Alexandr Niesov
        ER: 
            - method adds " " space and returns     
    */
    // std::string result = taskOne(data.c_str());
// char* TaskProcessor_1::taskOne(const char* name) {
    /*
        1 Відправити з клієнта на сервер своє ім’я,
        на сервері додати до імені своє прізвище та відпрарезультат на клієнт.
    */
//     static char result[20] = " ";
//     const char *firstName = "Alexandr";

//     if (strcmp(name, firstName) == 0) {
//         strcpy(result, firstName);
//         strcat(result, " Niesov");
//         return result;
//     }
//     return result;
// }


 