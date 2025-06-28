#include "player.h"
#include "config.h"
#include "game.h"

Player::Player(const sf::Color& color)
    : velocity(0.0f, 0.0f)
{
    shape.setRadius(Config::Player::RADIUS);
    shape.setOrigin(Config::Player::RADIUS, Config::Player::RADIUS);
    shape.setFillColor(color);
    shape.setPosition(middleOfTheScreen());
}


sf::Vector2f Player::middleOfTheScreen() {
    return {Config::Display::SCREEN_WIDTH / 2.0f, Config::Display::SCREEN_HEIGHT / 2.0f};
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

void Player::borderCollision(const sf::RenderWindow &window, sf::Sprite &mapSprite) {
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f bounds = mapSprite.getGlobalBounds().getSize();
    // pos.x = std::clamp(
    //     pos.x,
    //     Config::Player::RADIUS,
    //     static_cast<float>(window.getSize().x) - Config::Player::RADIUS
    // );
    // pos.y = std::clamp(
    //     pos.y,
    //     Config::Player::RADIUS,
    //     static_cast<float>(window.getSize().y) - Config::Player::RADIUS
    // );
    pos.x = std::clamp(
        pos.x,
        Config::Player::RADIUS,
        bounds.x - Config::Player::RADIUS
    );
    pos.y = std::clamp(
        pos.y,
        Config::Player::RADIUS,
        bounds.y - Config::Player::RADIUS
    );

    shape.setPosition(pos);
}

void Player::respawn() {
    setPosition(middleOfTheScreen());
}

