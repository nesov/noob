
#include "proc/StringParser.h"

/**
 * @brief Construct a new String Parser:: String Parser object
 * 
 * @param pattern takes patter as string
 */
StringParser::StringParser(const std::string& pattern):m_regexp(pattern) { }

/**
 * @brief main function 
 * 
 * @param input 
 */
void StringParser::parse(const std::string &input) {
    std::regex regexPattern(m_regexp);
    std::sregex_iterator it(input.begin(), input.end(), regexPattern);
    std::sregex_iterator end;

    for (; it != end; ++it) {
        m_matches.push_back(it -> str());
    }
}

/**
 * @brief method returns found results in vector format
 * 
 * @return std::vector<std::string> returns vector of results
 */
std::vector<std::string> StringParser::getParseResults() {
    return (m_matches.empty())?std::vector<std::string>():m_matches;
}
   