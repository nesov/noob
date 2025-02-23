cmake_minimum_required(VERSION 3.31.3)
project(final_work VERSION 1.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    message("OS    : ${CMAKE_SYSTEM_NAME}")
    # set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
    set(CMAKE_OSX_ARCHITECTURES "arm64")
    message("Arch  : ${CMAKE_OSX_ARCHITECTURES}")
endif()

include(custom_compile_flags)


option(ENABLE_TESTS "Enable tests" OFF)
if (${ENABLE_TESTS})
    enable_testing()
    # add_subdirectory(tests)
endif()


add_subdirectory(src/__ssapi)
add_subdirectory(src/__proc)
add_subdirectory(src/server)
# add_subdirectory(src/graphic_client)
add_subdirectory(src/console_client)
