
set(TARGET ssapilib)
set(SOURCE_DIR  src/TcpClient.cpp 
                src/TcpServer.cpp 
                src/Message.cpp
                src/Data.cpp
                src/INetworkService.cpp)



add_library(${TARGET} SHARED ${SOURCE_DIR})
target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRECTORIES})
set_target_properties(${TARGET} PROPERTIES FOLDER "Libraries")
