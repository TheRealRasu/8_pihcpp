cmake_minimum_required(VERSION 3.7)

project(8_pihcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 REQUIRED)

add_executable(8_pihcpp src/main.cpp)
target_link_libraries(8_pihcpp PRIVATE SDL2::SDL2)