cmake_minimum_required(VERSION 3.10)
project(ChinarEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE SOURCES "box.cpp" "../chinar/*.cpp")

add_executable(box ${SOURCES})

target_include_directories(box PRIVATE "../chinar")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
target_link_libraries(box PRIVATE SDL2::SDL2 SDL2_image)
