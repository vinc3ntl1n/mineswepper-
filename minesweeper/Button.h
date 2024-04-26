#ifndef MINESWEEPER_BUTTON_H
#define MINESWEEPER_BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
using namespace sf;
using namespace std;

class Button {
private:
    Vector2f pos;
    function<void()> clickFunc;
    Sprite* sprite;
public:
    Button(Vector2f _position, function<void()> _onClick);
    Vector2f getPosition() const;
    Sprite* getSprite() const;
    void setSprite(Sprite* _sprite);
    void onClick() const;
};

#endif //MINESWEEPER_BUTTON_H
