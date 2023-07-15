# CMakeList.txt : CMake project for sfml_czougi, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
# Add source to this project's executable.
add_library(GameController STATIC "GameController.cpp")

target_include_directories(Bullet PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GameController Shared Tank)
# TODO: Add tests and install targets if needed.
