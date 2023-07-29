cmake_minimum_required(VERSION 3.10)
project(Raytracing)

set(CMAKE_CXX_STANDARD 17)

file(GLOB cpp *.cpp)
add_executable(Raytracing ${cpp})