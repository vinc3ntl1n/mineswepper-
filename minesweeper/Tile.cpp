#include "Tile.h"
#include "Toolbox.h"

Tile::Tile(sf::Vector2f position) {
    minesNear = 0;
    state = State::HIDDEN;
    pos = position;
    isAMine = false;
}

sf::Vector2f Tile::getLocation() {
    return pos;
}

Tile::State Tile::getState() {
    return state;
}

std::array<Tile*, 8>& Tile::getNeighbors() {
    return neighbors;
}

void Tile::setState(Tile::State _state) {
    state = _state;
}

void Tile::setNeighbors(std::array<Tile *, 8> _neighbors) {
    neighbors = _neighbors;
}

void Tile::onClickLeft() {
    if (getState() == HIDDEN) {
        revealNeighbors();
    }
    state = State::REVEALED;
}

void Tile::onClickRight() {
    if (state == State::HIDDEN) {
        state = State::FLAGGED;
    }
    else if (state == State::FLAGGED) {
        state = State::HIDDEN;
    }
}

void Tile::draw() {
    Toolbox &tool = Toolbox::getInstance();
    sf::RenderWindow &window = tool.window;
    sf::Texture hidden;
    sf::Texture revealed;
    hidden.loadFromFile("images/tile_hidden.png");
    revealed.loadFromFile("images/tile_revealed.png");
    sf::Sprite tileSprite;
    if (getState() == State::REVEALED) {
        tileSprite.setTexture(revealed);
        tileSprite.setPosition(getLocation());
        window.draw(tileSprite);
        if (minesNear != 0) {
            sf::Texture numberTexture;
            sf::Sprite numberSprite;
            numberTexture.loadFromFile("images/number_" + std::to_string(minesNear) + ".png");
            numberSprite.setTexture(numberTexture);
            numberSprite.setPosition(getLocation());
            window.draw(numberSprite);
        }
    }
    else {
        tileSprite.setTexture(hidden);
        tileSprite.setPosition(getLocation());
        window.draw(tileSprite);
        if (getState() == State::FLAGGED) {
            sf::Texture flagTexture;
            sf::Sprite flagSprite;
            flagTexture.loadFromFile("images/flag.png");
            flagSprite.setTexture(flagTexture);
            flagSprite.setPosition(getLocation());
            window.draw(flagSprite);
        }
    }
}

void Tile::revealNeighbors() {
    if (getState() == HIDDEN) {
        setState(REVEALED);
        if (minesNear == 0) {
            for (Tile *a: getNeighbors()) {
                if (a != nullptr) {
                    a->revealNeighbors();
                }
            }
        }
    }
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
