
set(CMAKE_CXX_FLAGS_DEBUG           "-std=c++20 -O0 -g -Wall -fcolor-diagnostics -fansi-escape-codes -DDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-std=c++20 -O2 -g -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE         "-std=c++20 -O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_MINSIZEREL      "-std=c++20 -Os -DNDEBUG")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)