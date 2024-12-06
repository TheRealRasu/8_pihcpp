cmake_minimum_required(VERSION 3.7)

project(8_pihcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

add_library(Application src/Application/Application.cpp src/Application/Application.h)
target_link_libraries(Application SDL2::SDL2)
target_link_libraries(${PROJECT_NAME} Application)

include_directories(${PROJECT_NAME} ${SDL2_LIBRARIES})