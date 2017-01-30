cmake_minimum_required(VERSION 3.6)
project(DMFramework)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 14)

option(BUILD_TEST "Build tests." ON)

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_FILES
        include/DataHolder.h include/Ranked.h src/Ranked.cpp)

add_library(DMFramework ${SOURCE_FILES})

target_link_libraries(DMFramework variant)

if(BUILD_TEST)
    add_subdirectory(test)
endif()