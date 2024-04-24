#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Tile {
public:
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };

    Tile(sf::Vector2f position);
    sf::Vector2f getLocation();
    State getState();
    std::vector<Tile*>& getNeighbors();
    void setState(State _state);
    void addNeighbor(Tile* neighbor); // Function to add a neighbor
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
    std::vector<Tile*> neighbors; // Use vector instead of array
    Tile(const Tile& other);
    Tile& operator=(const Tile& other);
};

#endif //MINESWEEPER_TILE_H
