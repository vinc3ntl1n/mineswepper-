#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>

class Button {
public:
    Button(sf::Vector2f _position, std::function<void()> _onClick);

    sf::Vector2f getPosition() const;
    std::shared_ptr<sf::Sprite> getSprite() const;
    void setSprite(std::shared_ptr<sf::Sprite> _sprite);
    void onClick();

private:
    sf::Vector2f position;
    std::shared_ptr<sf::Sprite> sprite;
    std::function<void()> onClickFunction;
};

#endif // BUTTON_H
