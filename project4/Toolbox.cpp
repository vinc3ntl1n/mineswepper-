#include "Toolbox.h"
#include "minesweeper.h"

Toolbox::Toolbox() {
    showBombs = false;
    gameState = new GameState;
    sf::Vector2i dim = gameState->getDimensions();
    window.create(sf::VideoMode(800, 600), "P4 - Minesweeper, Vincent Lin");
    debugButtonTexture.loadFromFile("images/debug.png");
    newGameButtonTexture.loadFromFile("images/face_happy.png");
    testButton1Texture.loadFromFile("images/test_1.png");
    testButton2Texture.loadFromFile("images/test_2.png");
    testButton3Texture.loadFromFile("images/test_3.png");
    lossButtonTexture.loadFromFile("images/face_lose.png");
    winButtonTexture.loadFromFile("images/face_win.png");
    debugButtonSprite.setTexture(debugButtonTexture);
    newGameButtonSprite.setTexture(newGameButtonTexture);
    testButton1Sprite.setTexture(testButton1Texture);
    testButton2Sprite.setTexture(testButton2Texture);
    testButton3Sprite.setTexture(testButton3Texture);
    lossButtonSprite.setTexture(lossButtonTexture);
    winButtonSprite.setTexture(winButtonTexture);

    debugButton = new Button(sf::Vector2f((32.0f * dim.x) - 304.0f, 32.0f * (dim.y + 0.5f)), [this](){
        showBombs = !showBombs;
        sf::Vector2i dimensions = gameState->getDimensions();
        for (int x = 0; x < dimensions.x; x++) {
            for (int y = 0; y < dimensions.y; y++) {
                std::cout << "test";
            }
        }
    });

    debugButton->setSprite(&debugButtonSprite);
    winButton = new Button(sf::Vector2f((32.0f * dim.x / 2.0f) - 32.0f,32.0f * (dim.y + 0.5f)), [this]() {restart();});
    winButton->setSprite(&winButtonSprite);
    lossButton = new Button(sf::Vector2f((32.0f * dim.x / 2.0f) - 32.0f,32.0f * (dim.y + 0.5f)), [this]() {restart();});
    lossButton->setSprite(&lossButtonSprite);
    newGameButton = new Button(sf::Vector2f((32.0f * dim.x / 2.0f) - 32.0f,32.0f * (dim.y + 0.5f)), [this]() {restart();});
    newGameButton->setSprite(&newGameButtonSprite);
    testButton1 = new Button(sf::Vector2f((32.0f * dim.x) - 240.0f, 32.0f * (dim.y + 0.5f)), [this]() {
        delete gameState;
        gameState = new GameState("boards/testboard1.brd");
        gameState->setPlayStatus(GameState::PlayStatus::PLAYING);
        newGameButton->setSprite(&newGameButtonSprite);
    });
    testButton1->setSprite(&testButton1Sprite);
    testButton2 = new Button(sf::Vector2f((32.0f * dim.x) - 176.0f, 32.0f * (dim.y + 0.5f)), [this]() {
        delete gameState;
        gameState = new GameState("boards/testboard2.brd");
        gameState->setPlayStatus(GameState::PlayStatus::PLAYING);
        newGameButton->setSprite(&newGameButtonSprite);
    });
    testButton2->setSprite(&testButton2Sprite);
    testButton3 = new Button(sf::Vector2f((32.0f * dim.x) - 112.0f, 32.0f * (dim.y + 0.5f)), [this]() {
        delete gameState;
        gameState = new GameState("boards/testboard3.brd");
        gameState->setPlayStatus(GameState::PlayStatus::PLAYING);
        newGameButton->setSprite(&newGameButtonSprite);
    });
    testButton3->setSprite(&testButton3Sprite);
}

Toolbox::~Toolbox() {
    delete gameState;
    delete debugButton;
    delete newGameButton;
    delete testButton1;
    delete testButton2;
    delete testButton3;
    delete lossButton;
    delete winButton;
}

void Toolbox::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Handle other events here
        }

        // Update game state here

        // Clear the window
        window.clear();

        // Draw game objects here

        // Display the window
        window.display();
    }
}

Toolbox& Toolbox::getInstance() {
    static Toolbox inst;
    return inst;
}
