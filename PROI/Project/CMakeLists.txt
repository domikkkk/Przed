# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#

cmake_minimum_required (VERSION 3.8)
project("Scorched")
set(CMAKE_CXX_STANDARD 20)

# Add source to this project's executable.
include(FetchContent)
set(SFML_STATIC_LIBRARIES TRUE)
set(BUILD_SHARED_LIBS OFF)
set(THOR_SHARED_LIBS OFF)

FetchContent_Declare(
sfml
GIT_REPOSITORY "https://github.com/SFML/SFML.git"
GIT_TAG        "2.5.1"
)


if(NOT sfml_POPULATED)
FetchContent_Populate(sfml)
add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()
#add_executable (${PROJECT_NAME}.out "examples/TerrainTest.cpp"
#    "include/Scorched/Bullet/Bullet.hpp" "src/Scorched/Bullet/Bullet.cpp")


add_executable (${PROJECT_NAME}.out "src/Main.cpp" src/Scorched/Leaderboards/Leaderboards.cpp include/Scorched/Leaderboards/Leaderboards.hpp)

FetchContent_MakeAvailable(sfml)

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# resources library
include(CMakeRC)
cmrc_add_resource_library(Resources ALIAS Scorched::Resources NAMESPACE Resources
    src/Resources/bounce.png
    src/Resources/bullet.png
    src/Resources/Bullpen3D.ttf
    src/Resources/cluster.png
    src/Resources/huge.png
    src/Resources/sand.jpg
    src/Resources/small_cluster.png
    src/Resources/tank.png
    src/Resources/tank2.png
)
target_link_libraries(${PROJECT_NAME}.out Scorched::Resources)


add_subdirectory ("src/Scorched/Terrain")
add_subdirectory ("src/Scorched/Bullet")
add_subdirectory ("src/Scorched/Map")
# add_subdirectory ("src/Scorched/Resources")
add_subdirectory ("src/Scorched/Shared")
add_subdirectory ("src/Scorched/Tank")
add_subdirectory ("src/Scorched/GameController")
add_subdirectory ("src/Scorched/Leaderboards")

set_target_properties(sfml-graphics PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
set_target_properties(sfml-window PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
target_link_libraries(${PROJECT_NAME}.out sfml-graphics sfml-window Terrain Bullet Map Tank GameController Scorched::Resources)



# testing
add_executable(tests.out "test/test.cpp")

FetchContent_Declare(
gtest
GIT_REPOSITORY "https://github.com/google/googletest.git"
GIT_TAG        "release-1.11.0"
)

FetchContent_MakeAvailable(Gtest)

target_link_libraries(tests.out gtest Terrain Bullet Map Tank GameController Scorched::Resources)
