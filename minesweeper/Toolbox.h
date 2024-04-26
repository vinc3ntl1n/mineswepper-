#ifndef MINESWEEPER_TOOLBOX_H
#define MINESWEEPER_TOOLBOX_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"
#include "Tile.h"

class GameState;
class Tile;

class Toolbox {
    friend class GameState;
    friend class Tile;
    Toolbox();
    ~Toolbox();
public:
    sf::Texture winnerface;
    sf::Texture debug;
    sf::Texture newGame;
    sf::Texture testB1;
    sf::Texture testB2;
    sf::Texture testB3;
    sf::Texture loserface;
    sf::Sprite debugS;
    sf::Sprite newGameS;
    sf::Sprite testB1S;
    sf::Sprite testB2S;
    sf::Sprite testB3S;
    sf::Sprite loserfaceS;
    sf::Sprite winnerfaceS;
    sf::RenderWindow window;
    GameState* gameState;
    Button* debugButton;
    Button* newGameButton;
    Button* tB1;
    Button* tB2;
    Button* tB3;
    Button* lossButton;
    Button* winButton;
    bool showBombs;
    static Toolbox& getInstance();
};

#endif //MINESWEEPER_TOOLBOX_H
