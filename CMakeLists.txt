cmake_minimum_required(VERSION 3.5)
project(utilcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -O2 -g")

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cc")
file(GLOB_RECURSE HEADERS "include/*.hh")

if(SOURCES)
  add_library(utilcpp ${SOURCES})
  target_include_directories(utilcpp PUBLIC include)
endif()
