cmake_minimum_required(VERSION 3.0.0)
project(graphs VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-result -Wshadow")

add_subdirectory(src)
add_executable(graphs main.cpp) # put any .cpp file instead of "main.cpp" and run build

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
