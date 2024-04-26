#ifndef MINESWEEPER_MINE_H
#define MINESWEEPER_MINE_H

#include "Tile.h"

class mine : public Tile {
public:
    explicit mine(sf::Vector2f _position);
    void draw() override;
    void onClickLeft() override;
};

#endif //MINESWEEPER_MINE_H
