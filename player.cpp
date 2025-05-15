#include "Player.h"


Player::Player(sf::CircleShape _shape, const sf::Vector2f position, const sf::Vector2f& _velocity)
    : shape(std::move(_shape)), velocity(_velocity) {
    shape.setPosition(position.x, position.y);
}

sf::Vector2f Player::middleOfTheScreen() {
    return sf::Vector2f(SCREEN_WIDTH / 2.0f - radius, SCREEN_HEIGHT / 2.0f - radius);
}

void Player::setPosition(const sf::Vector2f& _position) {
    shape.setPosition(_position.x, _position.y);
}

void Player::setPosition(const float& _x, const float& _y) {
    shape.setPosition(_x, _y);
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}

void Player::setVelocity(const sf::Vector2f& _velocity) {
    velocity = _velocity;
}

void Player::setVelocity(const float& _x, const float& _y) {
    velocity.x = _x;
    velocity.y = _y;
}

sf::Vector2f Player::getVelocity() const {
    return velocity;
}

void Player::setFillColor(const sf::Color& _color) {
    shape.setFillColor(_color);
}

const sf::CircleShape& Player::getShape() const {
    return shape;
}

void Player::update() {
    shape.setPosition(shape.getPosition() + velocity);
}
