#pragma once 

#include <string>
#include <regex>
#include <vector>

/**
 * @brief String Parser Class
 * 
 */
class StringParser {
   
/**
 * @brief Public methods
 * 
 */
 public: 
   /**
    * @brief Construct a new String Parser object
    * 
    * @param regexp tasks regexp as a pattern
    */
    StringParser(const std::string& regexp);
    /**
     * @brief Main function parses input string 
     * 
     * @param input 
     */
    void parse(const std::string& input);
    /**
     * @brief Get the Parse Results object
     * 
     * @return std::vector<std::string> 
     */
    std::vector<std::string> getParseResults();
/**
 * @brief private methods
 * 
 */
 private:
 /**
  * @brief vector of results
  * 
  */
    std::vector<std::string> m_matches;
    /**
     * @brief string that holds regexp patterns
     * 
     */
    std::string m_regexp;
};
