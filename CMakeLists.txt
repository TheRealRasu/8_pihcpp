cmake_minimum_required(VERSION 3.7)

project(8_pihcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

add_library(Application src/Application/Application.cpp src/Application/Application.h src/Application/ApplicationDefines.h)
add_library(DisplayHandler src/Application/DisplayHandler.cpp src/Application/DisplayHandler.h src/Application/ApplicationDefines.h)
add_library(MemoryManager src/Application/MemoryManager.cpp src/Application/MemoryManager.h src/Application/ApplicationDefines.h)
add_library(Timer src/Timer/Timer.h src/Timer/Timer.cpp)
target_link_libraries(Application SDL2::SDL2)
target_link_libraries(DisplayHandler SDL2::SDL2)
target_link_libraries(${PROJECT_NAME} Application MemoryManager DisplayHandler Timer)

include_directories(${PROJECT_NAME} ${SDL2_LIBRARIES})