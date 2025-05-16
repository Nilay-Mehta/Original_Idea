#pragma once

#include <SFML/Graphics.hpp>

enum class ProjectileType {
    CirBullet,
    CapBullet
};


class Projectile {
public:
    Projectile(const sf::Vector2f& startPos, const sf::Vector2f& direction, ProjectileType _type);

    void update(float);
    void draw(sf::RenderWindow& window) const;
    bool isOffScreen(const sf::RenderWindow& window) const;
    int getDamage() const;
    ProjectileType getType() const;
    const sf::CircleShape& getCircleShape() const;
    sf::FloatRect getCapsuleBounds() const;


private:
    ProjectileType type;
    sf::Vector2f velocity;
    float speed;
    int damage;

    sf::CircleShape circleShape;
    sf::RectangleShape capsuleBody;
    sf::CircleShape capsuleHead;

    void setupCircle(const sf::Vector2f& startPos);
    void setupCapsule(const sf::Vector2f& startPos, const sf::Vector2f& direction);
};