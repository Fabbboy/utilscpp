cmake_minimum_required(VERSION 3.0)
project(utilcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -O2 -g")

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cc")
file(GLOB_RECURSE HEADERS "include/*.hh")

add_library(utilcpp ${SOURCES} ${HEADERS})
target_include_directories(utilcpp PUBLIC include)
