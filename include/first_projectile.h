#pragma once

#include "base_projectile.h"

class CirBullet : public BaseProjectile{
public:
    CirBullet(const sf::Vector2f& startPos, const sf::Vector2f& direction);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

    sf::FloatRect getBounds() const override;
    int getDamage() const override;
    bool isOffScreen(const sf::RenderWindow& window) const override;

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float speed = 800.0f;
    int damage = 20;
};