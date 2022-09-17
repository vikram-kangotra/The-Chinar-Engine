cmake_minimum_required(VERSION 3.10)

project(Proto-cpp VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB SRC "*.cpp" "*/*.cpp" "*/*/*.cpp")

add_executable(engine ${SRC})
target_link_libraries(engine -lSDL2)
