cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(beidou-grid-location-code-demo VERSION 1.0)

find_package(GTest REQUIRED)

include(CTest)
add_subdirectory(src)
enable_testing()
add_subdirectory(tests)
