cmake_minimum_required(VERSION 3.15)

project(greedy-scrabble)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS off)

set(CMAKE_DEBUG_POSTFIX "_d")

add_subdirectory(source)
add_subdirectory(applications/ConsoleSolver)