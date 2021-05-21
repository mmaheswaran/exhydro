cmake_minimum_required (VERSION 3.0)

project (exhydro)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(exhydro exhydro.cpp)
