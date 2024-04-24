#ifndef MINESWEEPER_TOOLBOX_H
#define MINESWEEPER_TOOLBOX_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "GameState.h"
#include "Button.h"

class GameState;
class Button;

class Toolbox {
public:
    static Toolbox& getInstance();
    ~Toolbox();

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
    std::unique_ptr<GameState> gameState;
    std::unique_ptr<Button> debugButton;
    std::unique_ptr<Button> newGameButton;
    std::unique_ptr<Button> testButton1;
    std::unique_ptr<Button> testButton2;
    std::unique_ptr<Button> testButton3;
    std::unique_ptr<Button> lossButton;
    std::unique_ptr<Button> winButton;
    bool showBombs;

private:
    Toolbox();
    Toolbox(const Toolbox&) = delete;
    void operator=(const Toolbox&) = delete;
};

#endif // MINESWEEPER_TOOLBOX_H
