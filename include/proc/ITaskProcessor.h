#pragma once

#include "ssapi/Data.h"

class ITaskProcessor {
    public: 
       virtual Data execute(Data& ) = 0;
       virtual ~ITaskProcessor();
   };
