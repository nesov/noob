
set(TARGET_NAME __executable)
set(INCLUDE_DIRECTORIES staticlib/include dynamiclib/include framework/include include)
set(SOURCE_DIR src/main.cpp)

add_executable(${TARGET_NAME} ${SOURCE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(${TARGET_NAME} PRIVATE __staticlib  PRIVATE __dynamiclib PRIVATE __dynamicFramework)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Applications")

