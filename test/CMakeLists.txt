enable_testing()

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRCS
        src/abstract_event_tests.cpp
        src/event_generator_tests.cpp
        src/transition_tests.cpp
        include/data_handler_impl.h
        include/state_impl.h
        src/relationship_tests.cpp
        src/transition_generator_tests.cpp
        src/relationship_generator_tests.cpp
        src/state_machine_tests.cpp)


add_executable(tests ${SRCS})
target_link_libraries(tests gtest gtest_main gmock DMFramework)
add_test(tests tests)

