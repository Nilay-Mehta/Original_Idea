#include "inv.h"

#include <cmath>
// #include <iostream>

Projectile::Projectile(const sf::Vector2f& startPos, const sf::Vector2f& direction, ProjectileType _type)
: type(_type)
{
    sf::Vector2f dir = direction;
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0)
        dir /= length;

    velocity = dir;
    // std::cout << "Velocity set to: (" << velocity.x << ", " << velocity.y << ")\n";

    speed = 800.0f;

    if (type == ProjectileType::CirBullet) {
        damage = 20;
        setupCircle(startPos);
    } else {
        damage = 30;
        setupCapsule(startPos, dir);
    }
}

void Projectile::setupCircle(const sf::Vector2f& startPos) {
    circleShape.setRadius(8.f);
    circleShape.setOrigin(8.f, 8.f);
    circleShape.setFillColor(sf::Color::White);
    circleShape.setPosition(startPos);
}

void Projectile::setupCapsule(const sf::Vector2f& startPos, const sf::Vector2f& direction) {
    float length = 30.0f;
    float width = 10.0f;

    capsuleBody.setSize({length, width});
    capsuleBody.setOrigin(length / 2, width / 2);
    capsuleBody.setFillColor(sf::Color::White);
    capsuleBody.setPosition(startPos);

    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
    capsuleBody.setRotation(angle);

    capsuleHead.setRadius(width / 2);
    capsuleHead.setOrigin(width / 2, width / 2);
    capsuleHead.setFillColor(sf::Color::White);
    capsuleHead.setPosition(startPos + direction * (length / 2));
}

void Projectile::update(float deltaTime) {
    sf::Vector2f offset = velocity * speed * deltaTime;

    if (type == ProjectileType::CirBullet) {
        circleShape.move(offset);
    } else {
        capsuleBody.move(offset);
        capsuleHead.move(offset);
    }
}

void Projectile::draw(sf::RenderWindow& window) const {
    if (type == ProjectileType::CirBullet) {
        window.draw(circleShape);
    } else {
        window.draw(capsuleBody);
        window.draw(capsuleHead);
    }
}

bool Projectile::isOffScreen(const sf::RenderWindow &window) const {
    sf::FloatRect bounds;

    if (type == ProjectileType::CirBullet)
        bounds = circleShape.getGlobalBounds();
    else {
        sf::FloatRect bodyBounds = capsuleBody.getGlobalBounds();
        sf::FloatRect headBounds = capsuleHead.getGlobalBounds();

        float left   = std::min(bodyBounds.left, headBounds.left);
        float top    = std::min(bodyBounds.top, headBounds.top);
        float right  = std::max(bodyBounds.left + bodyBounds.width, headBounds.left + headBounds.width);
        float bottom = std::max(bodyBounds.top + bodyBounds.height, headBounds.top + headBounds.height);

        bounds = sf::FloatRect(left, top, right - left, bottom - top);
    }

    const auto& boundsSize = window.getSize();
    return (
        bounds.left + bounds.width < 0 ||
        bounds.left > boundsSize.x ||
        bounds.top + bounds.height < 0 ||
        bounds.top > boundsSize.y
        );
}

int Projectile::getDamage() const {
    return damage;
}

ProjectileType Projectile::getType() const {
    return type;
}

const sf::CircleShape& Projectile::getCircleShape() const {
    return circleShape;
}

sf::FloatRect Projectile::getCapsuleBounds() const {
    // Capsule bounding box must cover both body and head
    sf::FloatRect bodyBounds = capsuleBody.getGlobalBounds();
    sf::FloatRect headBounds = capsuleHead.getGlobalBounds();

    float left = std::min(bodyBounds.left, headBounds.left);
    float top = std::min(bodyBounds.top, headBounds.top);
    float right = std::max(bodyBounds.left + bodyBounds.width, headBounds.left + headBounds.width);
    float bottom = std::max(bodyBounds.top + bodyBounds.height, headBounds.top + headBounds.height);

    return sf::FloatRect(left, top, right - left, bottom - top);
}
