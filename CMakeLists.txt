cmake_minimum_required(VERSION 3.10)
project(utilscpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cc")

add_library(utilscpp INTERFACE)
target_include_directories(utilscpp INTERFACE include)