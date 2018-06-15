cmake_minimum_required(VERSION 3.10)
project(wumpus LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(wumpus
        src/main.cpp
        src/Game.cpp
        src/Game.h
        # src/Random_utils.cpp
        src/Random_utils.h
        src/Maze.cpp
        src/Maze.h
        src/Actor.h
        src/Room.cpp
        src/Room.h)

add_executable(tests
        test/lib/catch.hpp
        test/wumpus-tests/test-main.cpp
        test/wumpus-tests/test-Random_utils.cpp
        src/Random_utils.h
        # src/Random_utils.cpp
        test/wumpus-tests/test-Maze.cpp
        src/Maze.h
        src/Maze.cpp
        test/wumpus-tests/test-Actor.cpp
        src/Actor.h
        test/wumpus-tests/test-Actor.cpp
        src/Game.cpp
        src/Game.h
        test/wumpus-tests/test-Game.cpp
        src/Room.cpp
        src/Room.h
        test/wumpus-tests/test-Room.cpp
        src/Game_text.h
        test/wumpus-tests/test-Game_text.cpp)
