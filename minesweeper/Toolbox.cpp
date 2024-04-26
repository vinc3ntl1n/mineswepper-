#include "Toolbox.h"
#include "minesweeper.h"
using namespace sf;

Toolbox::Toolbox() {
    showBombs = false;
    gameState = new GameState;
    Vector2i dim = gameState->getDimensions();
    window.create(VideoMode(800, 600), "P4 - Minesweeper, Vincent Lin");
    debug.loadFromFile("images/debug.png");
    newGame.loadFromFile("images/face_happy.png");
    testB1.loadFromFile("images/test_1.png");
    testB2.loadFromFile("images/test_2.png");
    testB3.loadFromFile("images/test_3.png");
    loserface.loadFromFile("images/face_lose.png");
    winnerface.loadFromFile("images/face_win.png");
    
    
    debugS.setTexture(debug);
    newGameS.setTexture(newGame);
    testB1S.setTexture(testB1);
    testB1S.setTexture(testB2);
    testB3S.setTexture(testB3);
    loserfaceS.setTexture(loserface);
    winnerfaceS.setTexture(winnerface);

    debugButton = new Button(Vector2f((32.0f * dim.x) - 304.0f, 32.0f * (dim.y + 0.5f)), [this]() {
        showBombs = !showBombs;
        Vector2i dimensions = gameState->getDimensions();
        for (int x = 0; x < dimensions.x; x++) {
            for (int y = 0; y < dimensions.y; y++) {
                std::cout << "test";
            }
        }
    });

    debugButton->setSprite(&debugS);
    winButton = new Button(Vector2f((32.0f * dim.x / 2.0f) - 32.0f,32.0f * (dim.y + 0.5f)), [this]() {restart();});
    winButton->setSprite(&winnerfaceS);
    lossButton = new Button(Vector2f((32.0f * dim.x / 2.0f) - 32.0f,32.0f * (dim.y + 0.5f)), [this]() {restart();});
    lossButton->setSprite(&loserfaceS);
    newGameButton = new Button(Vector2f((32.0f * dim.x / 2.0f) - 32.0f,32.0f * (dim.y + 0.5f)), [this]() {restart();});
    newGameButton->setSprite(&newGameS);
    tB1 = new Button(Vector2f((32.0f * dim.x) - 240.0f, 32.0f * (dim.y + 0.5f)), [this]() {
        delete gameState;
        gameState = new GameState("boards/testboard1.brd");
        gameState->setPlayStatus(GameState::PlayStatus::PLAYING);
        newGameButton->setSprite(&newGameS);
    });
    tB1->setSprite(&testB1S);
    tB2 = new Button(Vector2f((32.0f * dim.x) - 176.0f, 32.0f * (dim.y + 0.5f)), [this]() {
        delete gameState;
        gameState = new GameState("boards/testboard2.brd");
        gameState->setPlayStatus(GameState::PlayStatus::PLAYING);
        newGameButton->setSprite(&newGameS);
    });
    tB2->setSprite(&testB2S);
    tB3 = new Button(Vector2f((32.0f * dim.x) - 112.0f, 32.0f * (dim.y + 0.5f)), [this]() {
        delete gameState;
        gameState = new GameState("boards/testboard3.brd");
        gameState->setPlayStatus(GameState::PlayStatus::PLAYING);
        newGameButton->setSprite(&newGameS);
    });
    tB3->setSprite(&testB3S);
}

Toolbox& Toolbox::getInstance() {
    static Toolbox inst;
    return inst;
}

Toolbox::~Toolbox() {
    delete gameState;
    delete debugButton;
    delete newGameButton;
    delete tB1;
    delete tB2;
    delete tB3;
    delete lossButton;
    delete winButton;
}
