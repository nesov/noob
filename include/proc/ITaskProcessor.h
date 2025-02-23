#pragma once

#include "ssapi/Data.h"

// class ITaskProcessor {
//     public: 
//        virtual Data execute(Data& ) = 0;
//        virtual ~ITaskProcessor();
//    };

class ITaskProcessor {
    public: 
       virtual std::string execute(std::string& ) = 0;
       virtual ~ITaskProcessor();
   };
