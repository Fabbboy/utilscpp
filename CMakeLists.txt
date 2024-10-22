cmake_minimum_required(VERSION 3.10)
project(utilscpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cc")

if(SOURCES)
  add_library(utilscpp ${SOURCES})
  target_link_directories(utilscpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
else()
  add_library(utilscpp INTERFACE)
  target_include_directories(utilscpp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()