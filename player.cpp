#include "player.h"
#include "config.h"
#include "game.h"

Player::Player(const sf::Color& color)
    : velocity(0.0f, 0.0f)
{
    shape.setRadius(RADIUS);
    shape.setOrigin(RADIUS, RADIUS);
    shape.setFillColor(color);
    shape.setPosition(middleOfTheScreen());
}


sf::Vector2f Player::middleOfTheScreen() {
    return {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
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

void Player::setPosition(const sf::Vector2f& _position) {
    shape.setPosition(_position);
}

void Player::setPosition(const float x, const float y) {
    shape.setPosition(x, y);
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}

void Player::borderCollision(const sf::RenderWindow &window) {
    sf::Vector2f pos = shape.getPosition();

    pos.x = std::clamp(pos.x, RADIUS, static_cast<float>(window.getSize().x) - RADIUS);
    pos.y = std::clamp(pos.y, RADIUS, static_cast<float>(window.getSize().y) - RADIUS);

    shape.setPosition(pos);
}
