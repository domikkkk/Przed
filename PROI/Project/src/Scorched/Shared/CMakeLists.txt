# CMakeList.txt : CMake project for sfml_czougi, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)
# Add source to this project's executable.
add_library(Shared STATIC "Entity.cpp")

target_include_directories(Shared PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)

target_link_libraries(Shared sfml-graphics Map)
# TODO: Add tests and install targets if needed.
