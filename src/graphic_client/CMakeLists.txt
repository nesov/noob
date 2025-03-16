
set(TARGET_NAME graphic_client)
set(INCLUDE include 
            ${CMAKE_SOURCE_DIR}/include)

set(SOURCES src/main.cpp
            src/Application.cpp
            src/MainViewController.cpp
)


project(${TARGET_NAME})
include(fltk_dep)

add_executable(${TARGET_NAME} WIN32 MACOSX_BUNDLE ${SOURCES})
target_include_directories(${TARGET_NAME} PRIVATE ${fltk_BINARY_DIR} ${fltk_SOURCE_DIR} ${INCLUDE})
target_link_libraries(${TARGET_NAME} PRIVATE fltk fltk_gl fltk_images fltk_png fltk_jpeg fltk_z PRIVATE ssapi)

if(APPLE)
    target_link_libraries(${TARGET_NAME} PRIVATE "-framework Cocoa") 
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Applications")