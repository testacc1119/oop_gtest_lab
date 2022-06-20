cmake_minimum_required(VERSION 3.8)

# Alias
set(This Matrix)

# Languages for project (creating project)
project(${This} C CXX)

# Language standarts
set(CMAKE_C_STANDART 99)
set(CMAKE_CXX_STANDART 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)
add_subdirectory(Matrix)

# Useful: List of header and source files for our project
set(Headers
    Matrix.hpp
)

set(Sources
    Matrix.cpp
)

# Building library for testing
add_library(${This} STATIC ${Headers} ${Sources})

add_subdirectory(Tests)