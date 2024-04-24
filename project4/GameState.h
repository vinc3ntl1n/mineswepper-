#ifndef MINESWEEPER_GAMESTATE_H
#define MINESWEEPER_GAMESTATE_H

#include "Tile.h"
#include "mine.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <memory> // Added for smart pointers

class GameState {
public:
    enum PlayStatus { WIN, LOSS, PLAYING };

    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    GameState(const char* filepath);
    ~GameState(); // Destructor to deallocate memory

    // Copy constructor and assignment operator are deleted to prevent copying
    GameState(const GameState&) = delete;
    GameState& operator=(const GameState&) = delete;

    int getFlagCount();
    int getMineCount();
    Tile* getTile(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);
    sf::Vector2i getDimensions();
    std::vector<std::vector<std::unique_ptr<Tile>>>& getTiles(); // Changed to return unique_ptr

private:
    void setNeighborsAndMines(); // Declaration of helper function
    sf::Vector2i dimensions;
    int numMines;
    PlayStatus playStatus;
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles; // Changed to unique_ptr
};

#endif //MINESWEEPER_GAMESTATE_H
