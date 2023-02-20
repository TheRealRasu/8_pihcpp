cmake_minimum_required(VERSION 3.7)

project(8_pihcpp)

find_package(SDL2 REQUIRED)
include_directories(8_pihcpp lib/SDL2/include)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

add_executable(8_pihcpp src/main.cpp)
target_link_libraries(8_pihcpp lib/SDL2/lib/x64/SDL2)
