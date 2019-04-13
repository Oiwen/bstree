cmake_minimum_required(VERSION 2.8)
project(bstree)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror -std=c++17 -O0 -g")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

include_directories("./include")
file(GLOB SOURCES "./src/*.cpp")

add_executable(bstree ${SOURCES})
