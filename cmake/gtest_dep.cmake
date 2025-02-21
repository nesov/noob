include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/main.zip
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)