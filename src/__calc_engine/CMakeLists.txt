set(TARGET calclib)
set(INCLUDE_DIRECTORIES include)
set(SOURCE_DIR  src/calcengine.cpp
                src/task_algo.cpp)


add_library(${TARGET} STATIC ${SOURCE_DIR})
target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRECTORIES})

set_target_properties(${TARGET} PROPERTIES FOLDER "Libraries")