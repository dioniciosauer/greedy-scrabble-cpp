cmake_minimum_required(VERSION 3.15)

project(greedy-scrabble)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS off)

set(CMAKE_DEBUG_POSTFIX "_d")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/96f4ce02a3a78d63981c67acbd368945d11d7d70.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(source)
add_subdirectory(tests)
add_subdirectory(applications/ConsoleSolver)