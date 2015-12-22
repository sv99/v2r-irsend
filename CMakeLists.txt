cmake_minimum_required(VERSION 3.1)
project(v2r_irsend)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

include(FindPkgConfig)

add_subdirectory(src)
# add_subdirectory(tests)
