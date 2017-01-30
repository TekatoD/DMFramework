enable_testing()

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRCS src/DataHolderTests.cpp)


add_executable(tests ${SRCS})
target_link_libraries(tests gtest gtest_main gmock DMFramework)
add_test(tests tests)

