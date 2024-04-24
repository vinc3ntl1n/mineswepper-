#ifndef MINESWEEPER_MINE_H
#define MINESWEEPER_MINE_H

#include "Tile.h"
#include "Toolbox.h"

class mine : public Tile {
public:
    mine(sf::Vector2f _position);
    void draw() override;
    void onClickLeft() override;
};

#endif //MINESWEEPER_MINE_H
