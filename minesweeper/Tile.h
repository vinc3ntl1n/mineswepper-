#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H

#include <SFML/Graphics.hpp>
#include <array>

class GameState;

class Tile {
public:
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };
    Tile(sf::Vector2f position);
    sf::Vector2f getLocation();
    State getState();
    std::array<Tile*, 8>& getNeighbors();
    void setState(State _state);
    void setNeighbors(std::array<Tile*, 8> _neighbors);
    virtual void onClickLeft();
    void onClickRight();
    virtual void draw();
    bool isMine();
    void setMine(bool x);
    void setNumMines(int number);
    int getMinesNear();
protected:
    void revealNeighbors();
private:
    int minesNear;
    bool isAMine;
    State state;
    sf::Vector2f pos;
    std::array<Tile*, 8> neighbors;
};

#endif //MINESWEEPER_TILE_H
