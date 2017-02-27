cmake_minimum_required(VERSION 3.6)
project(DMFramework)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 14)

option(BUILD_TEST "Build tests." ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_FILES
        include/ranked.h
        src/ranked.cpp
        include/abstract_state.h
        include/abstract_event.h
        include/condition.h
        include/event_data_handler.h
        include/transition.h
        include/data_handler.h
        include/transition_generator.h include/probability_event.h include/relationship.h)

add_library(DMFramework ${SOURCE_FILES})

if(BUILD_TEST)
    add_subdirectory(test)
endif()