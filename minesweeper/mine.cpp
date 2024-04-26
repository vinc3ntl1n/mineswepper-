#include "mine.h"
#include "Toolbox.h"

mine::mine(sf::Vector2f _position) : Tile(_position) {
    setMine(true);
}

void mine::draw() {
    Toolbox& a = Toolbox::getInstance();
    sf::RenderWindow& wind = a.window;//referce for the window

    static sf::Texture mineTexture, tileTexture, flagTexture;
    static sf::Sprite mineSprite, tileSprite, flagSprite;
    static bool texturesLoaded = false;

    if (!texturesLoaded) {
        // Load textures only once
        mineTexture.loadFromFile("images/mine.png");//loads the game textutres
        tileTexture.loadFromFile("images/tile_hidden.png");
        flagTexture.loadFromFile("images/flag.png");
        texturesLoaded = true;
    }
    mineSprite.setTexture(mineTexture);
    mineSprite.setPosition(getLocation());
    tileSprite.setTexture(tileTexture);
    tileSprite.setPosition(getLocation());
    flagSprite.setTexture(flagTexture);
    flagSprite.setPosition(getLocation());

    if (getState() == State::EXPLODED) {//if the square that mines get hit
        wind.draw(mineSprite);
    }
    else if (getState() == State::FLAGGED && a.showBombs) {
        wind.draw(mineSprite);
        wind.draw(flagSprite);
    }
    else {
        wind.draw(tileSprite);
        if (a.showBombs) {
            wind.draw(mineSprite);
        }
        else if (getState() == FLAGGED) {
            wind.draw(flagSprite);
        }
    }
}

void mine::onClickLeft() {
    if (getState() == State::HIDDEN) {
        setState(State::EXPLODED);
        static sf::Texture loseTexture;
        static bool textureLoaded = false;

        if (!textureLoaded) {
            loseTexture.loadFromFile("images/face_lose.png");
            textureLoaded = true;
        }

        sf::Sprite loseSprite;
        loseSprite.setTexture(loseTexture);
        Toolbox::getInstance().newGameButton->setSprite(&loseSprite);//makes the face :( very sad when lose
        Toolbox::getInstance().gameState->setPlayStatus(GameState::LOSS);
    }
}
