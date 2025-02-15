
set(TARGET_NAME server)
set(INCLUDE_DIRECTORIES src/__ssapilib/include 
                        src/__calc_engine/include include)
set(SOURCE_DIR src/main.cpp 
                src/AsyncServer.cpp 
                src/JsonObject.cpp 
                src/MessageHandler.cpp)

add_executable(${TARGET_NAME} ${SOURCE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(${TARGET_NAME} PRIVATE calclib  PRIVATE ssapilib )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Applications")

