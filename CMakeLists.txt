cmake_minimum_required(VERSION 3.24)
project(APT-ASSIGNMENT1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(APT-ASSIGNMENT1
        main.cpp
        milestone4.h
        Node.cpp
        Node.h
        NodeList.cpp
        NodeList.h
        PathSolver.cpp
        PathSolver.h
        Types.h)
