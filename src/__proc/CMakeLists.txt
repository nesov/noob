set(TARGET proc)
# set(INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR  src/ITaskProcessor.cpp
                src/TaskProcessor_1.cpp 
                src/TaskProcessor_2.cpp)


add_library(${TARGET} STATIC ${SOURCE_DIR})
target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRECTORIES})

set_target_properties(${TARGET} PROPERTIES FOLDER "Libraries")