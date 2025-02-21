
#include <string>
#include "ssapi/Data.h"
#include "proc/TaskProcessor_1.h"

Data TaskProcessor_1::execute(Data& data) {
    std::string input = data.StringData;
    std::string result = taskOne(input.c_str());
   
    Data outData;
    outData.StringData = result.c_str();
    return outData;
}

char * TaskProcessor_1::taskOne(const char *name) {
    /*
        1 Відправити з клієнта на сервер своє ім’я,
        на сервері додати до імені своє прізвище та відпрарезультат на клієнт.
    */
    static char result[20] = "";
    const char *firstName = "Alexandr";

    if (strcmp(name, firstName) == 0) {
        strcpy(result, firstName);
        strcat(result, " Niesov");
        return result;
    }
    return result;
}
 