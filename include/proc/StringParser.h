#pragma once 

#include <string>
#include <regex>
#include <vector>


class StringParser {
    public: 
        StringParser(const std::string& regexp);
        void parse(const std::string& input);
    private:
        std::vector<std::string>& m_matches;
        std::string m_regexp;
};