cmake_minimum_required(VERSION 3.10)
project(commonc)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(commonc INTERFACE)
target_include_directories(commonc INTERFACE include)
