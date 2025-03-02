
project(tests VERSION 1.0 LANGUAGES CXX)

set(TEST_TARGET __tests)
set(TEST_SOURCES    src/main.cpp
                    # src/tests.cpp
                    src/TaskProcessor_1_Tests.cpp
                    src/TaskProcessor_2_Tests.cpp
                    src/TaskProcessor_4_Tests.cpp
)
set(EXTERNAL_SOURCES
            ${CMAKE_SOURCE_DIR}/src/__proc/src/TaskProcessorFactory.cpp
            ${CMAKE_SOURCE_DIR}/src/__proc/src/TaskProcessor_1.cpp
            ${CMAKE_SOURCE_DIR}/src/__proc/src/TaskProcessor_2.cpp
            ${CMAKE_SOURCE_DIR}/src/__proc/src/TaskProcessor_4.cpp
            ${CMAKE_SOURCE_DIR}/src/__proc/src/StringParser.cpp
)

include(gtest_dep)

add_executable(${TEST_TARGET} ${TEST_SOURCES} ${EXTERNAL_SOURCES})
target_include_directories(${TEST_TARGET} PRIVATE ${INCLUDE_DIRECTORIES}  ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${TEST_TARGET} PUBLIC GTest::gtest_main GTest::gtest)

gtest_discover_tests(${TEST_TARGET} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

set_target_properties(${TEST_TARGET} PROPERTIES FOLDER "Tests")
