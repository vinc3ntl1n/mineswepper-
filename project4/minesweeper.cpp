#include "minesweeper.h"
#include <SFML/Graphics.hpp> // Include SFML graphics library

Toolbox& tools = Toolbox::getInstance();  // Update to match the instance in your code

int launch() {
    restart();
    sf::RenderWindow& window = tools.window;  // initializes window
    sf::Vector2i dim = tools.gameState->getDimensions();
    sf::Event event;
    while (window.isOpen()) {
        render();
        window.display();
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {  // handles closing game
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {  // handles mouse clicking
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;
                // debug button
                if (mouseX >= (32.0f * dim.x) - 304.0f - 32.0f && mouseX <= (32.0f * dim.x) - 304.0f + 32.0f && mouseY >= 32.0f * (dim.y + 0.5f) && mouseY <= 32.0f * (dim.y + 0.5f) + 64.0f) {
                    std::cout << "debug" << std:: endl;
                    toggleDebugMode();
                }
                    // new game button
                else if (mouseX >= (32.0f * dim.x / 2.0f) - 32.0f - 32.0f && mouseX <= (32.0f * dim.x / 2.0f) - 32.0f + 32.0f && mouseY >= 32.0f * (dim.y + 0.5f) && mouseY <= 32.0f * (dim.y + 0.5f) + 64.0f) {
                    std::cout << "new game" << std::endl;
                    tools.newGameButton->onClick();
                }
                    // test board 1 button
                else if (mouseX >= (32.0f * dim.x) - 240.0f - 32.0f && mouseX <= (32.0f * dim.x) - 240.0f + 32.0f && mouseY >= 32.0f * (dim.y + 0.5f) && mouseY <= 32.0f * (dim.y + 0.5f) + 64.0f) {
                    tools.testButton1->onClick();
                    std::cout << "test 1" << std::endl;
                }
                    // test board 2 button
                else if (mouseX >= (32.0f * dim.x) - 176.0f - 32.0f && mouseX <= (32.0f * dim.x) - 176.0f + 32.0f && mouseY >= 32.0f * (dim.y + 0.5f) && mouseY <= 32.0f * (dim.y + 0.5f) + 64.0f) {
                    tools.testButton2->onClick();
                    std::cout << "test 2" << std::endl;
                }
                    // test board 3 button
                else if (mouseX >= (32.0f * dim.x) - 112.0f - 32.0f && mouseX <= (32.0f * dim.x) - 112.0f + 32.0f && mouseY >= 32.0f * (dim.y + 0.5f) && mouseY <= 32.0f * (dim.y + 0.5f) + 64.0f) {
                    tools.testButton3->onClick();
                    std::cout << "test 3" << std::endl;
                }
                else {
                    // handles tile clicks
                    sf::Vector2i tileCoords;
                    tileCoords = sf::Vector2i(mouseX / 32, mouseY / 32);
                    if (tileCoords.x < dim.x && tileCoords.y < dim.y) {
                        Tile* tile = tools.gameState->getTile(tileCoords.x, tileCoords.y);
                        if (tools.gameState->getPlayStatus() == GameState::PLAYING && tile != nullptr) {
                            if (event.mouseButton.button == sf::Mouse::Right) {
                                tile->onClickRight();
                            }
                            else if (event.mouseButton.button == sf::Mouse::Left) {
                                tile->onClickLeft();
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void restart() {
    delete tools.gameState;
    tools.gameState = new GameState;
    tools.gameState->setPlayStatus(GameState::PLAYING);
    tools.newGameButton->setSprite(&tools.newGameButtonSprite);
}

void render() {
    sf::RenderWindow& window = tools.window;
    int flagsPlaced = tools.gameState->getMineCount() - tools.gameState->getFlagCount();  // holds starting flags (mine count) - flags on board
    sf::Vector2i dimensions = tools.gameState->getDimensions();
    int totalTiles = dimensions.x * dimensions.y;
    int revealedTiles = 0;
    sf::Texture digits;
    digits.loadFromFile("images/digits.png");
    tools.window.draw(*tools.debugButton->getSprite());  // draws debug button
    if (tools.gameState->getPlayStatus() == GameState::PLAYING) {  // draws new game button with varying sprites depending on play status
        tools.window.draw(*tools.newGameButton->getSprite());
    }
    else if (tools.gameState->getPlayStatus() == GameState::LOSS) {
        tools.window.draw(*tools.lossButton->getSprite());
    }
    else if (tools.gameState->getPlayStatus() == GameState::WIN) {
        tools.window.draw(*tools.winButton->getSprite());
    }

    tools.window.draw(*tools.testButton1->getSprite());  // draws test button 1
    tools.window.draw(*tools.testButton2->getSprite());  // draws test button 2
    tools.window.draw(*tools.testButton3->getSprite());  // draws test button 3
    for (int x = 0; x < tools.gameState->getTiles().size(); x++) {  // draws each tile
        for (int y = 0; y < tools.gameState->getTiles()[0].size(); y++) {
            tools.gameState->getTile(x, y)->draw();
            if (tools.gameState->getTile(x, y)->getState() == Tile::REVEALED) {  // counts number of revealed tiles while drawng
                revealedTiles++;
            }
        }
    }
    if (revealedTiles == totalTiles - tools.gameState->getMineCount()) {  // if every tile other than mine tile is revealed
        tools.newGameButton->setSprite(&tools.winButtonSprite);
        tools.gameState->setPlayStatus(GameState::WIN);
    }
    int digit1, digit2, digit3;
    if (flagsPlaced > 0) {  // used to set digit sprites
        digit1 = (flagsPlaced / 100) % 10;
        digit2 = (flagsPlaced / 10) % 10;
        digit3 = flagsPlaced % 10;
    }
    else {  // in the case that flag count is negative
        digit1 = (-flagsPlaced / 100) % 10;
        digit2 = (-flagsPlaced / 10) % 10;
        digit3 = -flagsPlaced % 10;
    }
    // sets each digit sprite
    sf::Sprite d1(digits, sf::IntRect(digit1 * 21, 0, 21, 32));
    sf::Sprite d2(digits, sf::IntRect(digit2 * 21, 0, 21, 32));
    sf::Sprite d3(digits, sf::IntRect(digit3 * 21, 0, 21, 32));
    sf::Sprite negative(digits, sf::IntRect(10 * 21, 0, 21, 32));
    // sets digit positions
    d1.setPosition(33, 32.0f * (dimensions.y + 0.5) + 16);
    d2.setPosition(54, 32.0f * (dimensions.y + 0.5) + 16);
    d3.setPosition(75, 32.0f * (dimensions.y + 0.5) + 16);
    negative.setPosition(33, 32.0f * (dimensions.y + 0.5) + 16);
    if (flagsPlaced < 0) {  // in the case that flag count is negative, draw negative sign instead
        tools.window.draw(negative);
    }
    else {
        tools.window.draw(d1);
    }
    tools.window.draw(d2);
    tools.window.draw(d3);
}

void toggleDebugMode() {
    tools.showBombs = !tools.showBombs;
}

bool getDebugMode() {
    return tools.showBombs;
}

int gameLoop() {
    return true;
}

int main() {
    return launch();
}
