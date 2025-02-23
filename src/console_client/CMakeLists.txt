
set(TARGET_NAME console_client)

set(SOURCE_DIR src/main.cpp

)
project(${TARGET_NAME})


add_executable(${TARGET_NAME} ${SOURCE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${TARGET_NAME} PRIVATE ssapi PRIVATE proc )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Applications")