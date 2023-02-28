cmake_minimum_required(VERSION 3.10)

project(Dron_Dragonfly)

set(INC ${Dron_Dragonfly_SOURCE_DIR}/inc)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Dron_Dragonfly_SOURCE_DIR})

add_compile_options(-Wall -Wextra -Wpedantic -pedantic -g)

add_subdirectory(src)

