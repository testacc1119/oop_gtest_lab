cmake_minimum_required(VERSION 3.8)

set(This Tests)

set(Sources
    Tests.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    Bubbles
)

add_test(
    NAME ${This}
    COMMAND ${This}
)