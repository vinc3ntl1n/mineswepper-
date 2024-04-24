mine::mine(sf::Vector2f _position) : Tile(_position) {
    setMine(true);
}

void mine::draw() {
    Toolbox& a = Toolbox::getInstance();
    sf::RenderWindow& wind = a.window;
    sf::Texture mineTexture;
    sf::Sprite mineSprite;
    sf::Texture tileTexture;
    sf::Sprite tileSprite;
    sf::Texture flagTexture;
    sf::Sprite flagSprite;
    mineTexture.loadFromFile("images/mine.png");
    mineSprite.setTexture(mineTexture);
    mineSprite.setPosition(getLocation());
    tileTexture.loadFromFile("images/tile_hidden.png");
    tileSprite.setTexture(tileTexture);
    tileSprite.setPosition(getLocation());
    flagTexture.loadFromFile("images/flag.png");
    flagSprite.setTexture(flagTexture);
    flagSprite.setPosition(getLocation());
    if (getState() == State::EXPLODED) {
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
        sf::Texture loseTexture;
        sf::Sprite loseSprite;
        loseTexture.loadFromFile("images/face_lose.png");
        loseSprite.setTexture(loseTexture);
        Toolbox::getInstance().newGameButton->setSprite(&loseSprite);
        Toolbox::getInstance().gameState->setPlayStatus(GameState::LOSS);
    }
}
