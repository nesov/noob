#include <algorithm>
#include <string>
#include <vector>

namespace calcucations {

    // string.h
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

    template<typename T>
    T taskTwo(T a, T b) {
        /*
            2 Відправити на сервер два числа, знайти їх суму та повернути результат клієнту.
        */
       return a + b;
    }

    template <typename T>
    T taskThree(T a, T b){
        /*
            3 Відправити на клієнт два числа, знайти їх добуток та повернути результат серверу.
        */
        return a * b;
    }
    // algoritm.h
    template <typename T>
    T taskFour(std::vector<T>& arr){
        /*
        4 Відправити на сервер масив, знайти його максимальний елемент та повернути результат кліє
        */
        T max = std::max_element(arr.begin(),arr.end());
        return max;
    }
    // algotritm.h
    template<typename T>
    T taskFive (T number) {
        /*
        5 Відправити на сервер число, сервер перевіряє, чи є воно більшим за введене на ньому значеня кщо так, 
        то повертає на клієнт своє число, 
        інакше повертає клієнту його ж число.
        */
    //    std::random_device rd; 
    //    std::mt19937 mersenne(rd());
        // T secretNumber = mersenne();
        T secretNumber {5};
        return (secretNumber > number) ? secretNumber : number;
    }

    bool taskSix(int num){

        /*
        6 Відправити на сервер число, сервер перевіряє, чи є це число паліндромом.
            Якщо так, то відправляє на клієнт «Yes», якщо ні, то повертає «No».
        */
        // std::string str = std::to_string(num);
        // std::string revStr = str;
        // std::reverse(revStr.begin(), revStr.end());
        // return str == revStr;

        if (num < 0) return false;
        int original = num, reversed = 0;
        while (num > 0) {
            int digit = num % 10;
            reversed = reversed * 10 + digit;
            num /= 10;
        }
        return original == reversed;
    }


    //algoritm.h
    template<typename T>
    void taskSeven(std::vector<T>& arr){
        /*
        Відправити з сервера на клієнт масив чисел, відсортувати їх за зростанням та повернути на сервер.
        */
       std::sort(arr.begin(), arr.end(), std::less<T>());
    }


    int taskEigth(const char* str){
        /*
        8 Відправити на сервер повідомлення, знайти у ньому кількість літер «a», та відправити на кл результат.
        */
       int acounter {0};
       for (int i = 0; str[i]; i++ )
            if (str[i] == 'a') acounter++;
       return acounter;
    }

    std::vector<int> taskNine(const char* message){
        /*
        9 Відправити на клієнт повідомлення, знайти його довжину і відправити відповідну кількість нулів на сервер.
        */
        size_t size = strlen(message);
        std::vector<int> result(size, 0);
        return result;
    }

    bool taskTen(const char* message){
        /*
            10 Відправити повідомлення на сервер, перевірити чи є в ньому цифри, 
            якщо так, то відправити повідомлення «Yes» на клієнт, інакше «No»
        */
        size_t size = strlen(message);
        for (int i = 0; i < size; i++){
            if (std::isdigit(message[i])!= 0){
                return true;
                break;
            }
        }
        return false;
    }

    /*
    Відправити з клієнта на сервер своє прізвище, 
    на сервері додати до прізвища своє ім’я та відправити результат на клієнт.
    */

}