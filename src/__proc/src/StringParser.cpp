
#include "proc/StringParser.h"

void StringParser::parse(const std::string &input) {
    std::regex regexPattern(m_regexp);
    std::sregex_iterator it(input.begin(), input.end(), regexPattern);
    std::sregex_iterator end;

    for (; it != end; ++it) {
        m_matches.push_back(it -> str());
    }
}
    