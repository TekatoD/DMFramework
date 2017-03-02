cmake_minimum_required(VERSION 3.6)
project(DMFramework CXX)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_TEST "Build tests." ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_FILES
        include/abstract_state.h
        include/abstract_event.h
        include/event_data_handler.h
        include/transition.h
        include/data_handler.h
        include/transition_generator.h
        include/relationship.h
        include/relationship_generator.h
        include/state_machine.h)

add_library(DMFramework INTERFACE)
target_include_directories(DMFramework INTERFACE include)
target_sources(DMFramework INTERFACE ${SOURCE_FILES})

if(BUILD_TEST)
    add_subdirectory(test)
endif()