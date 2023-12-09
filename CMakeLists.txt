cmake_minimum_required(VERSION 3.25)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(main
src/main.cpp
src/SmartPointers/UniquePtr/UniquePtr.hpp
src/SmartPointers/UniquePtr/UniquePtr.tpp
src/SmartPointers/SharedPtr/SharedPtr.hpp
src/SmartPointers/SharedPtr/SharedPtr.tpp
)

add_executable(tests
src/Tests.cpp
src/SmartPointers/UniquePtr/UniquePtr.hpp
src/SmartPointers/UniquePtr/UniquePtr.tpp
src/SmartPointers/SharedPtr/SharedPtr.hpp
src/SmartPointers/SharedPtr/SharedPtr.tpp
)

add_executable(main src/main.cpp)