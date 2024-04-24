#include "Button.h"

Button::Button(sf::Vector2f _position, std::function<void()> _onClick)
        : position(_position), onClickFunction(_onClick), sprite(nullptr) {}

sf::Vector2f Button::getPosition() const {
    return position;
}

std::shared_ptr<sf::Sprite> Button::getSprite() const {
    return sprite;
}

void Button::setSprite(std::shared_ptr<sf::Sprite> _sprite) {
    sprite = _sprite;
}

void Button::onClick() {
    if (onClickFunction) {
        onClickFunction();
    }
}
