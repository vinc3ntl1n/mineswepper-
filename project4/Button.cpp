#include "Button.h"

Button::Button(sf::Vector2f _position, std::function<void()> _onClick)
        : pos(_position), clickFunc(std::move(_onClick)), sprite(nullptr) {}

sf::Vector2f Button::getPosition() const {
    return pos;
}

sf::Sprite* Button::getSprite() const {
    return sprite;
}

void Button::setSprite(sf::Sprite* _sprite) {
    sprite = _sprite;
    if (sprite) {
        sprite->setPosition(pos.x - sprite->getLocalBounds().width / 2, pos.y);
    }
}

void Button::onClick() {
    clickFunc();
}
