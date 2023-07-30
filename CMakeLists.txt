cmake_minimum_required(VERSION 3.10)
project(Raytracing)

set(CMAKE_CXX_STANDARD 17)

include_directories(Material)
include_directories(Hittable)
include_directories(Ray)
include_directories(Tool)

file(GLOB cpp *.cpp)

add_executable(Raytracing ${cpp})