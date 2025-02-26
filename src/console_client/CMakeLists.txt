
set(TARGET_NAME _console_client)
project(${TARGET_NAME})

set(SOURCE_DIR src/main.cpp
                src/ConsoleApplication.cpp
                src/BaseDialog.cpp
                src/MainDialog.cpp
                src/WantPlayAgainDialog.cpp
                src/Cache.cpp)


add_executable(${TARGET_NAME} ${SOURCE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${TARGET_NAME} PRIVATE ssapi)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Applications")