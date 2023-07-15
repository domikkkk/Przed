cmake_minimum_required(VERSION 3.11)
project(BCD)

set(CMAKE_CXX_STANDARD 11)

include_directories(Lib)

add_library(BCDLib Lib/BCD.cpp Lib/BCD.h)

add_executable(BCD main.cpp)
target_link_libraries(BCD PUBLIC BCDLib)

message("CLion > Visual Studio")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
if(WIN32)
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif(WIN32)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(BCDTest BCDtest/BCDtest.cpp)
target_link_libraries(BCDTest PUBLIC gtest_main BCDLib)

include(GoogleTest)
gtest_discover_tests(BCDTest)