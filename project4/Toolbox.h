#ifndef MINESWEEPER_TOOLBOX_H
#define MINESWEEPER_TOOLBOX_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"

class GameState; // Forward declaration
class Button; // Forward declaration

class Toolbox {
    friend class GameState;
    friend class Tile;
    Toolbox();
    ~Toolbox();
public:
    sf::Texture winButtonTexture;
    sf::Texture debugButtonTexture;
    sf::Texture newGameButtonTexture;
    sf::Texture testButton1Texture;
    sf::Texture testButton2Texture;
    sf::Texture testButton3Texture;
    sf::Texture lossButtonTexture;
    sf::Sprite debugButtonSprite;
    sf::Sprite newGameButtonSprite;
    sf::Sprite testButton1Sprite;
    sf::Sprite testButton2Sprite;
    sf::Sprite testButton3Sprite;
    sf::Sprite lossButtonSprite;
    sf::Sprite winButtonSprite;
    sf::RenderWindow window;
    GameState* gameState;
    Button* debugButton;
    Button* newGameButton;
    Button* testButton1;
    Button* testButton2;
    Button* testButton3;
    Button* lossButton;
    Button* winButton;
    bool showBombs;
    static Toolbox& getInstance();
    void run(); // Added run() declaration
};

#endif //MINESWEEPER_TOOLBOX_H
