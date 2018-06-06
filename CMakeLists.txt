cmake_minimum_required(VERSION 3.10)
project(wumpus)

set(CMAKE_CXX_STANDARD 14)

add_executable(wumpus src/main.cpp src/Game.cpp src/Game.h src/Random_int.h test/wumpus-tests/test-Random_int.cpp)