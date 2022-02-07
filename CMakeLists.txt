cmake_minimum_required(VERSION 3.21)
project(hw01)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(hw01
        Game.cpp
        Game.h
        Player.h Player.cpp main.cpp)
