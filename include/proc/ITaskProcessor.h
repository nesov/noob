#pragma once

#include <string>

/**
 * @brief  Task processor interface
 * 
 */
class ITaskProcessor {
 public: 
 /**
  * @brief virtual function for execution process
  * 
  * @return  returns result in format std::string 
  */
   virtual std::string execute(const std::string& ) = 0;

   /**
    * @brief Destroy the ITaskProcessor object
    * 
    */
   virtual ~ITaskProcessor() = default;
};
