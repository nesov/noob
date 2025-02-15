
set(TARGET ssapilib)
set(INCLUDE_DIRECTORIES include)

set(SOURCE_DIR src/ssapi_client.cpp src/ssapi_server.cpp)
add_library(${TARGET} SHARED ${SOURCE_DIR})
target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRECTORIES})

set_target_properties(${TARGET} PROPERTIES FOLDER "Libraries")
