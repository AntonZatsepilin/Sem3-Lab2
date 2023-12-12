cmake_minimum_required(VERSION 3.25)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(main
src/main.cpp
src/Data_structures/data_structures.cpp
src/Data_structures/data_structures.hpp
src/Sequences/sequences.hpp
src/Sequences/sequences.cpp
src/Menus/menus.hpp
src/Menus/menus.cpp) 