cmake_minimum_required(VERSION 3.14)
project(TriGoLTests)

# C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main with SDL3
find_package(SDL3 REQUIRED)
add_executable(main src/main.cpp src/utils.cpp)
target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE SDL3::SDL3)

# Tests with Catch2
find_package(Catch2 3 REQUIRED)
add_executable(tests tests/test_utils.cpp src/utils.cpp)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
