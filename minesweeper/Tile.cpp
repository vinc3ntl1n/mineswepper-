#include "Tile.h"
#include "Toolbox.h"
#include <SFML/Graphics.hpp>
#include <memory>

Tile::Tile(sf::Vector2f position) : pos(position), minesNear(0), state(HIDDEN), isAMine(false) {}

sf::Vector2f Tile::getLocation() const {
    return pos;
}

Tile::State Tile::getState() const {
    return state;
}

std::array<std::shared_ptr<Tile>, 8> Tile::getNeighbors() const {
    return neighbors;
}

void Tile::setState(State _state) {
    state = _state;
}

void Tile::setNeighbors(const std::array<std::shared_ptr<Tile>, 8>& _neighbors) {
    neighbors = _neighbors;
}

void Tile::onClickLeft() {
    if (getState() == HIDDEN) {
        revealNeighbors();
    }
    setState(REVEALED);
}

void Tile::onClickRight() {
    if (state == HIDDEN) {
        setState(FLAGGED);
    } else if (state == FLAGGED) {
        setState(HIDDEN);
    }
}

void Tile::draw() {
    Toolbox &tool = Toolbox::getInstance();
    sf::RenderWindow &window = tool.window;
    sf::Sprite tileSprite;
    tileSprite.setPosition(getLocation());
    if (getState() == REVEALED) {
        sf::Texture &revealed = tool.getTexture("revealed");
        tileSprite.setTexture(revealed);
        window.draw(tileSprite);
        if (minesNear != 0) {
            sf::Sprite numberSprite;
            numberSprite.setTexture(tool.getTexture("number_" + std::to_string(minesNear)));
            numberSprite.setPosition(getLocation());
            window.draw(numberSprite);
        }
    } else {
        sf::Texture &hidden = tool.getTexture("hidden");
        tileSprite.setTexture(hidden);
        window.draw(tileSprite);
        if (getState() == FLAGGED) {
            sf::Sprite flagSprite;
            flagSprite.setTexture(tool.getTexture("flag"));
            flagSprite.setPosition(getLocation());
            window.draw(flagSprite);
        }
    }
}

void Tile::revealNeighbors() {
    if (getState() == HIDDEN && !isMine()) {
        setState(REVEALED);
        if (minesNear == 0) {
            for (auto &neighbor : getNeighbors()) {
                if (neighbor && neighbor->getState() == HIDDEN) {
                    neighbor->revealNeighbors();
                }
            }
        }
    }
}

bool Tile::isMine() const {
    return isAMine;
}

void Tile::setMine(bool x) {
    isAMine = x;
}

void Tile::setNumMines(int number) {
    minesNear = number;
}

int Tile::getMinesNear() const {
    return minesNear;
}
