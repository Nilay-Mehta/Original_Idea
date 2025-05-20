#include "first_projectile.h"
#include <cmath>

CirBullet::CirBullet(const sf::Vector2f& startPos, const sf::Vector2f& direction) {
    float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = (len != 0) ? direction / len : sf::Vector2f(0.f, 0.f);

    shape.setRadius(8.f);
    shape.setOrigin(8.f, 8.f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(startPos);
}

void CirBullet::update(float deltaTime) {
    shape.move(velocity * speed * deltaTime);
}

void CirBullet::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect CirBullet::getBounds() const {
    return shape.getGlobalBounds();
}

int CirBullet::getDamage() const {
    return damage;
}

bool CirBullet::isOffScreen(const sf::RenderWindow& window) const {
    sf::FloatRect b = shape.getGlobalBounds();
    auto size = window.getSize();
    return (b.left + b.width < 0 || b.left > size.x || b.top + b.height < 0 || b.top > size.y);
}
