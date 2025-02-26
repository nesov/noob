

set(TARGET ssapi)
set(SOURCE_DIR  
                src/TcpSocketClient.cpp 
                src/TcpSocketServer.cpp 
                src/SocketBase.cpp
                src/NetworkServiceFactory.cpp
                src/Message.cpp
    )


add_library(${TARGET} SHARED ${SOURCE_DIR})
target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRECTORIES})
set_target_properties(${TARGET} PROPERTIES FOLDER "Libraries")
