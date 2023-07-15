# CMakeList.txt : CMake project for sfml_czougi, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


add_library(Terrain STATIC "Triangulate.cpp" "Terrain.cpp")

target_include_directories(Terrain PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Terrain sfml-graphics Scorched::Resources)
