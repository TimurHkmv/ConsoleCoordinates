cmake_minimum_required(VERSION 3.10)
project(ConsoleCoordinates)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(ConsoleCoordinates 
    src/main.cpp
    src/point.cpp    
)