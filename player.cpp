#include "Player.h"


Player::Player(const sf::Color& color)
    : velocity(0.0f, 0.0f)
{
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setPosition(middleOfTheScreen());
}


sf::Vector2f Player::middleOfTheScreen() {
    return sf::Vector2f(SCREEN_WIDTH / 2.0f - radius, SCREEN_HEIGHT / 2.0f - radius);
}

void Player::setFillColor(const sf::Color& _color) {
    shape.setFillColor(_color);
}

const sf::CircleShape& Player::getShape() const {
    return shape;
}

void Player::move(const sf::Vector2f &offset) {
    shape.move(offset);
}
