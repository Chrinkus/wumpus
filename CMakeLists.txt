cmake_minimum_required(VERSION 3.10)
project(wumpus LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(wumpus
        src/main.cpp
        src/Game.cpp
        src/Game.h
        src/Random_int.h
        src/Maze.cpp src/Maze.h)

add_executable(tests
        test/lib/catch.hpp
        test/wumpus-tests/test-main.cpp
        test/wumpus-tests/test-Random_int.cpp
        src/Random_int.h
        test/wumpus-tests/test-Maze.cpp
        src/Maze.h
        src/Maze.cpp)
