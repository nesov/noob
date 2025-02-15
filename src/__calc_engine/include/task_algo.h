#pragma once 
#include <vector>

namespace calculations {
    // string.h
    char* taskOne(const char* name);

    template<typename T> T  taskTwo(T a, T b) {

        /*
            2 Відправити на сервер два числа, знайти їх суму та повернути результат клієнту.
        */
       return a + b;
    }

    template <typename T> T taskThree(T a, T b){
        /*
            3 Відправити на клієнт два числа, знайти їх добуток та повернути результат серверу.
        */
        return a * b;
    }

    template <typename T> T taskFour(std::vector<T>& arr){
        /*
        4 Відправити на сервер масив, знайти його максимальний елемент та повернути результат кліє
        */
        T max = std::max_element(arr.begin(),arr.end());
        return max;
    }

    template<typename T> T  taskFive (T number) {
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

    bool taskSix(int num);
    template<typename T> void taskSeven(std::vector<T>& arr){
        /*
        Відправити з сервера на клієнт масив чисел, відсортувати їх за зростанням та повернути на сервер.
        */
       std::sort(arr.begin(), arr.end(), std::less<T>());
    }

    int taskEigth(const char* str);

    std::vector<int> taskNine(const char* message);

    bool taskTen(const char* message);

}