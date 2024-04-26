#include "Button.h"
#include <utility>

void Button::setSprite(sf::Sprite* _sprite) {
    if (_sprite) {
        sprite = _sprite;
        sf::FloatRect bounds = sprite->getLocalBounds();//sets the sprite to the appritoate sprite 
        float w = bounds.width;
        float x = pos.x - w / 2;
        sprite->setPosition(x, pos.y);
    }
}
sf::Vector2f Button::getPosition() const {
    return pos;
}
Button::Button(sf::Vector2f _position, std::function<void()> _onClick)
        : pos(_position), clickFunc(_onClick), sprite(nullptr) {}

sf::Sprite* Button::getSprite() const {
    return sprite;
}

void Button::onClick() const {
    clickFunc();
}



