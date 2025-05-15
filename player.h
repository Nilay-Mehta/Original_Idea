// Created by nilay on 13-05-2025.

#pragma once

#include <SFML/Graphics.hpp>
#include "config.h"

// Defining the player class
class Player {
public:
    static constexpr int radius = 50;

    Player(sf::CircleShape _shape, const sf::Vector2f position, const sf::Vector2f& _velocity);

    static sf::Vector2f middleOfTheScreen();

    void setPosition(const sf::Vector2f& _position);
    void setPosition(const float& _x, const float& _y);
    sf::Vector2f getPosition() const;

    void setVelocity(const sf::Vector2f& _velocity);
    void setVelocity(const float& _x, const float& _y);
    sf::Vector2f getVelocity() const;

    void setFillColor(const sf::Color& _color);

    const sf::CircleShape& getShape() const;

    void update();

private:
    sf::CircleShape shape;      // Circle shape for the player (could be changed later to something else)
    sf::Vector2f velocity;
};
