
project(tests VERSION 1.0 LANGUAGES CXX)

set(TEST_TARGET __tests)
set(TEST_SOURCES    src/main.cpp
                    src/tests.cpp
                    src/tests_new.cpp
)

include(gtest_dep)

add_executable(${TEST_TARGET} ${TEST_SOURCES})
target_include_directories(${TEST_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${TEST_TARGET} PUBLIC GTest::gtest_main GTest::gtest)

gtest_discover_tests(${TEST_TARGET} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
# execute_process(COMMAND ctest WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "TestApps")
