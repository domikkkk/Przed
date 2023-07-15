cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)
# Add source to this project's executable.
add_library(Leaderboards STATIC "Leaderboards.cpp")

target_include_directories(Leaderboards PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)

target_link_libraries(Leaderboards)
# TODO: Add tests and install targets if needed.
