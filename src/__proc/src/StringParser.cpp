
#include "proc/StringParser.h"

StringParser::StringParser(const std::string& pattern):m_regexp(pattern) { }

void StringParser::parse(const std::string &input) {
    std::regex regexPattern(m_regexp);
    std::sregex_iterator it(input.begin(), input.end(), regexPattern);
    std::sregex_iterator end;

    for (; it != end; ++it) {
        m_matches.push_back(it -> str());
    }
}

std::vector<std::string> StringParser::getParseResults() {
    return (m_matches.empty())?std::vector<std::string>():m_matches;
}
   