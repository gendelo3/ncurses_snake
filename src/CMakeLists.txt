cmake_minimum_required(VERSION 3.10)
project(Snake)

set(CMAKE_CXX_STANDARD 20)

add_executable(Snake main.cpp Snake.cpp)

target_link_libraries(${PROJECT_NAME} ncurses)