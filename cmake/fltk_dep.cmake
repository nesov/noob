

set (FLTK_COMMIT "branch-1.3" CACHE STRING "FLTK branch name, tag, or commit")

include(FetchContent)

set(FLTK_BUILD_TEST OFF CACHE BOOL " " FORCE)
if(UNIX AND NOT APPLE) 
    set(OPTION_USE_PANGO ON CACHE BOOL " " FORCE)
endif()

FetchContent_Declare(FLTK
    GIT_REPOSITORY      https://github.com/fltk/fltk
    GIT_TAG             "${FLTK_COMMIT}"
)

FetchContent_MakeAvailable(FLTK)