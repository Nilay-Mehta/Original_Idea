#pragma once

#include <SFML/Graphics.hpp>

class BaseProjectile {
public:
    virtual ~BaseProjectile() = default;

    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;

    virtual sf::FloatRect getBounds() const = 0;
    virtual int getDamage() const = 0;
    virtual bool isOffScreen(const sf::RenderWindow& window, sf::Sprite &mapSprite) const = 0;
};