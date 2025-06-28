#include "second_projectile.h"
#include <cmath>

CapBullet::CapBullet(const sf::Vector2f& startPos, const sf::Vector2f& direction) {
    float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = (len != 0) ? direction / len : sf::Vector2f(0.f, 0.f);

    float width = 10.f;
    float length = 30.f;

    body.setSize({length, width});
    body.setOrigin(length / 2, width / 2);
    body.setFillColor(sf::Color::Yellow);
    body.setPosition(startPos);

    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
    body.setRotation(angle);

    head.setRadius(width / 2);
    head.setOrigin(width / 2, width / 2);
    head.setFillColor(sf::Color::Yellow);
    head.setPosition(startPos + velocity * (length / 2));
}

void CapBullet::update(float deltaTime) {
    sf::Vector2f offset = velocity * speed * deltaTime;
    body.move(offset);
    head.move(offset);
}

void CapBullet::draw(sf::RenderWindow& window) const {
    window.draw(body);
    window.draw(head);
}

sf::FloatRect CapBullet::getBounds() const {
    sf::FloatRect b = body.getGlobalBounds();
    sf::FloatRect h = head.getGlobalBounds();

    float left = std::min(b.left, h.left);
    float top = std::min(b.top, h.top);
    float right = std::max(b.left + b.width, h.left + h.width);
    float bottom = std::max(b.top + b.height, h.top + h.height);

    return sf::FloatRect(left, top, right - left, bottom - top);
}

int CapBullet::getDamage() const {
    return damage;
}

bool CapBullet::isOffScreen(const sf::RenderWindow& window, sf::Sprite &mapSprite) const {
    sf::FloatRect b = getBounds();
    // auto size = window.getSize();
    auto size = mapSprite.getGlobalBounds();
    return (b.left + b.width < 0 || b.left > size.width || b.top + b.height < 0 || b.top > size.height);
}
