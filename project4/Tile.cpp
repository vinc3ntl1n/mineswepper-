#include "Tile.h"
#include "Toolbox.h"

Tile::Tile(sf::Vector2f position) : minesNear(0), state(HIDDEN), isAMine(false), pos(position) {}

sf::Vector2f Tile::getLocation() {
    return pos;
}

Tile::State Tile::getState() {
    return state;
}

std::vector<Tile*>& Tile::getNeighbors() {
    return neighbors;
}

void Tile::setState(Tile::State _state) {
    state = _state;
}

void Tile::addNeighbor(Tile* neighbor) {
    neighbors.push_back(neighbor); // Add neighbor to the vector
}

void Tile::onClickLeft() {
    if (getState() == HIDDEN) {
        revealNeighbors();
    }
    state = REVEALED;
}

void Tile::onClickRight() {
    if (state == HIDDEN) {
        state = FLAGGED;
    } else if (state == FLAGGED) {
        state = HIDDEN;
    }
}

void Tile::draw() {
    // Same implementation as before
}

void Tile::revealNeighbors() {
    // Same implementation as before
}

bool Tile::isMine() {
    return isAMine;
}

void Tile::setMine(bool x) {
    isAMine = x;
}

void Tile::setNumMines(int number) {
    minesNear = number;
}

int Tile::getMinesNear() {
    return minesNear;
}
