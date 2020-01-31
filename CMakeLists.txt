cmake_minimum_required(VERSION 3.15)
project(otus_hw15)

set(CMAKE_CXX_STANDARD 17)

add_executable(otus_hw15 main.cpp)
target_link_libraries(otus_hw15 dlib)
target_link_libraries(otus_hw15 openblas)