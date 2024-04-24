#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <array>
#include "Tile.h" // Ensure Tile class is included correctly

class GameState {
public:
    enum PlayStatus { WIN, LOSS, PLAYING };

    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    GameState(const char* filepath);

    int getFlagCount() const;
    int getMineCount() const;
    std::shared_ptr<Tile> getTile(int x, int y) const;
    PlayStatus getPlayStatus() const;
    void setPlayStatus(PlayStatus _status);

private:
    sf::Vector2i dimensions;
    int numMines;
    std::vector<std::vector<std::shared_ptr<Tile>>> tiles;
    PlayStatus playStatus;
};

#endif // GAMESTATE_H
