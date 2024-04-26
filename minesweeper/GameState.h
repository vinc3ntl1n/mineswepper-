    #ifndef MINESWEEPER_GAMESTATE_H
    #define MINESWEEPER_GAMESTATE_H
    #include "Tile.h"
    #include "mine.h"
    #include <SFML/Graphics.hpp>
    #include <fstream>
    #include <iostream>

    class mine;
    class Tile;

    class GameState {

    public:
        enum PlayStatus { WIN, LOSS, PLAYING };
        GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
        GameState(const char* filepath);
        int getFlagCount();
        int getMineCount();
        Tile* getTile(int x, int y);
        PlayStatus getPlayStatus();
        void setPlayStatus(PlayStatus _status);
        sf::Vector2i getDimensions();
        std::vector<std::vector<Tile*>> getTiles();
    private:
        sf::Vector2i dimensions;
        int mineNum;
        PlayStatus currstatus;
        std::vector<std::vector<Tile*>> tiles;
    };

    #endif //MINESWEEPER_GAMESTATE_H