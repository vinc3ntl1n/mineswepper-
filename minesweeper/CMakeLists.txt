# Inspired by: https://www.youtube.com/watch?v=PInJvpQSRHw

cmake_minimum_required(VERSION 3.26)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)

add_executable(minesweeper
        minesweeper.cpp
        minesweeper.h
        Toolbox.cpp
        Toolbox.h
        Button.cpp
        Button.h
        Tile.cpp
        Tile.h
        GameState.cpp
        GameState.h
        mine.cpp
        mine.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Documents/Projects/Test/SFML/include/SFML)
target_link_libraries(minesweeper sfml-system sfml-window sfml-graphics sfml-audio)