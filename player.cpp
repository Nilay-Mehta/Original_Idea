#include "player.h"

#include <cmath>
#include <iostream>

#include "game.h"

Player::Player(const sf::Color& color)
    : velocity(0.0f, 0.0f)
{
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(color);
    shape.setPosition(middleOfTheScreen());
}


sf::Vector2f Player::middleOfTheScreen() {
    return sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
}

void Player::setFillColor(const sf::Color& _color) {
    shape.setFillColor(_color);
}

const sf::CircleShape& Player::getShape() const {
    return shape;
}

void Player::move(const sf::Vector2f &offset) {
    // std::cout << "Move offset: " << offset.x << ", " << offset.y << std::endl;
    shape.move(offset);
}

void Player::setPosition(const sf::Vector2f &_position) {
    shape.setPosition(_position);
}

void Player::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}

void Player::borderCollision(const sf::RenderWindow &window) {
    sf::Vector2f pos = shape.getPosition();
    float RADIUS = radius;

    pos.x = std::clamp(pos.x, RADIUS, static_cast<float>(window.getSize().x) - RADIUS);
    pos.x = std::clamp(pos.y, RADIUS, static_cast<float>(window.getSize().y) - RADIUS);

    shape.setPosition(pos);
}
