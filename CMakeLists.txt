cmake_minimum_required(VERSION 3.17)
project(untitled5)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR C:/LOL/include)
set(SDL2_LIB_DIR C:/LOL/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(untitled5 main.cpp game_of_life.cpp game_of_life.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)