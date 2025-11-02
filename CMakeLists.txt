cmake_minimum_required(VERSION 3.14)
project(TriGoLTests)

# Find Catch2
find_package(Catch2 3 REQUIRED)

# These tests use the Catch2-provided main
add_executable(tests tests/test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
