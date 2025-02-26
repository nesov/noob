

set(TARGET proc)

set(            SOURCE_DIR  
                src/StringParser.cpp
                src/TaskProcessor_1.cpp 
                src/TaskProcessor_2.cpp
                src/TaskProcessor_4.cpp
    )


add_library(${TARGET} STATIC ${SOURCE_DIR})
target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRECTORIES})

set_target_properties(${TARGET} PROPERTIES FOLDER "Libraries")