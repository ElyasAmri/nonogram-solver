cmake_minimum_required(VERSION 3.20)
project(nonogram_solver)

set(CMAKE_CXX_STANDARD 20)

add_executable(nonogram_solver main.cpp
        src/Board.cpp
        src/Line.cpp
        src/Cell.cpp
        )
