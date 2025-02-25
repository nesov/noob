#pragma once


 /*
         R"(-?\d+(\.\d+)?)" — отрицательные и дробные числа.
         R"(\b[A-Za-z]{4,}\b)" — слова длиной 4+ букв.
         R"(-?\d+(\.\d+)?)" - числа
         R"(\w+@\w+\.\w+)" — email-адреса.
         R"([a-zA-Z]+)" - слова
*/
// constexpr std::string kPatternForTask2 = R"(-?\d+(\.\d+)?)";

constexpr const char* kPatternForTask1 = R"(\bOleksandr\b)";
constexpr const char* kPatternForTask2 = R"(-?\d+(\.\d+)?)";





