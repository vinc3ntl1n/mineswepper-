cmake_minimum_required(VERSION 3.27)
project(project4)

set(CMAKE_CXX_STANDARD 17)

add_executable(project4
        Button.cpp
        Button.h
        GameState.cpp
        GameState.h
        mine.cpp
        mine.h
        minesweeper.cpp
        minesweeper.h
        Tile.cpp
        Tile.h
        Toolbox.cpp
        Toolbox.h
)

set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(project4 sfml-system sfml-window sfml-graphics sfml-audio)