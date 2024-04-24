#ifndef MINESWEEPER_BUTTON_H
#define MINESWEEPER_BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
private:
    sf::Vector2f pos;
    std::function<void()> clickFunc;
    sf::Sprite* sprite;

public:
    Button(sf::Vector2f _position, std::function<void()> _onClick);
    sf::Vector2f getPosition() const;
    sf::Sprite* getSprite() const;
    void setSprite(sf::Sprite* _sprite);
    void onClick();
};

#endif // MINESWEEPER_BUTTON_H
