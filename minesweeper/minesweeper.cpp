#include "minesweeper.h"

Toolbox& tools = Toolbox::getInstance();

int launch() {
    restart();
    sf::RenderWindow& window = tools.window;
    sf::Vector2i dim = tools.gameState->getDimensions();
    sf::Event event;
    while (window.isOpen()) {
        render();
        window.display();
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                if (mouseX >= (32.0f * dim.x) - 304.0f - 32.0f && mouseX <= (32.0f * dim.x) - 304.0f + 32.0f && mouseY >= 32.0f * (dim.y + 0.5f) && mouseY <= 32.0f * (dim.y + 0.5f) + 64.0f) {
                    std::cout << "debug" << std:: endl;
                    toggleDebugMode();
                }
                else if (mouseX >= (32.0f * dim.x / 2.0f) - 32.0f - 32.0f && mouseX <= (32.0f * dim.x / 2.0f) - 32.0f + 32.0f && mouseY >= 32.0f * (dim.y + 0.5f) && mouseY <= 32.0f * (dim.y + 0.5f) + 64.0f) {
                    std::cout << "new game" << std::endl;
                    tools.newGameButton->onClick();
                }
                else if (mouseX >= (32.0f * dim.x) - 240.0f - 32.0f && mouseX <= (32.0f * dim.x) - 240.0f + 32.0f && mouseY >= 32.0f * (dim.y + 0.5f) && mouseY <= 32.0f * (dim.y + 0.5f) + 64.0f) {
                    tools.tB1->onClick();
                    std::cout << "test 1" << std::endl;
                }
                else if (mouseX >= (32.0f * dim.x) - 176.0f - 32.0f && mouseX <= (32.0f * dim.x) - 176.0f + 32.0f && mouseY >= 32.0f * (dim.y + 0.5f) && mouseY <= 32.0f * (dim.y + 0.5f) + 64.0f) {
                    tools.tB2->onClick();
                    std::cout << "test 2" << std::endl;
                }
                else if (mouseX >= (32.0f * dim.x) - 112.0f - 32.0f && mouseX <= (32.0f * dim.x) - 112.0f + 32.0f && mouseY >= 32.0f * (dim.y + 0.5f) && mouseY <= 32.0f * (dim.y + 0.5f) + 64.0f) {
                    tools.tB3->onClick();
                    std::cout << "test 3" << std::endl;
                }
                else {
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
    tools.newGameButton->setSprite(&tools.newGameS);
}

void render() {
    sf::RenderWindow& window = tools.window;
    int flagsPlaced = tools.gameState->getMineCount() - tools.gameState->getFlagCount();
    sf::Vector2i dimensions = tools.gameState->getDimensions();
    int totalTiles = dimensions.x * dimensions.y;
    int revealedTiles = 0;
    sf::Texture digits;
    digits.loadFromFile("images/digits.png");
    tools.window.draw(*tools.debugButton->getSprite());
    if (tools.gameState->getPlayStatus() == GameState::PLAYING) {
        tools.window.draw(*tools.newGameButton->getSprite());
    }
    else if (tools.gameState->getPlayStatus() == GameState::LOSS) {
        tools.window.draw(*tools.lossButton->getSprite());
    }
    else if (tools.gameState->getPlayStatus() == GameState::WIN) {
        tools.window.draw(*tools.winButton->getSprite());
    }

    tools.window.draw(*tools.tB1->getSprite());
    tools.window.draw(*tools.tB2->getSprite());
    tools.window.draw(*tools.tB3->getSprite());
    for (int i = 0; i < tools.gameState->getTiles().size(); i++) {
        for (int j = 0; j < tools.gameState->getTiles()[0].size(); j++) {
            tools.gameState->getTile(i, j)->draw();
            if (tools.gameState->getTile(i, j)->getState() == Tile::REVEALED) {
                revealedTiles++;
            }
        }
    }
    if (revealedTiles == totalTiles - tools.gameState->getMineCount()) {
        tools.newGameButton->setSprite(&tools.winnerfaceS);
        tools.gameState->setPlayStatus(GameState::WIN);
    }
    int digit1, digit2, digit3;
    if (flagsPlaced > 0) {
        digit1 = (flagsPlaced / 100) % 10;
        digit2 = (flagsPlaced / 10) % 10;
        digit3 = flagsPlaced % 10;
    }
    else {
        digit1 = (-flagsPlaced / 100) % 10;
        digit2 = (-flagsPlaced / 10) % 10;
        digit3 = -flagsPlaced % 10;
    }
    sf::Sprite d1(digits, sf::IntRect(digit1 * 21, 0, 21, 32));
    sf::Sprite d2(digits, sf::IntRect(digit2 * 21, 0, 21, 32));
    sf::Sprite d3(digits, sf::IntRect(digit3 * 21, 0, 21, 32));
    sf::Sprite negative(digits, sf::IntRect(10 * 21, 0, 21, 32));
    d1.setPosition(33, 32.0f * (dimensions.y + 0.5) + 16);
    d2.setPosition(54, 32.0f * (dimensions.y + 0.5) + 16);
    d3.setPosition(75, 32.0f * (dimensions.y + 0.5) + 16);
    negative.setPosition(33, 32.0f * (dimensions.y + 0.5) + 16);
    if (flagsPlaced < 0) {
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
