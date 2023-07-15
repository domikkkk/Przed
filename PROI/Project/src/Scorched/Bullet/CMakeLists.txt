# CMakeList.txt : CMake project for sfml_czougi, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
# Add source to this project's executable.
add_library(Bullet STATIC "Bullet.cpp")

target_include_directories(Bullet PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Bullet Shared sfml-graphics Scorched::Resources)
# TODO: Add tests and install targets if needed.
