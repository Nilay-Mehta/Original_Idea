// Created by nilay on 13-05-2025.

#pragma once

#include <SFML/Graphics.hpp>

// Defining the player class
class Player {
public:
    explicit Player(const sf::Color& color);
    static sf::Vector2f middleOfTheScreen();
    void setFillColor(const sf::Color& _color);
    const sf::CircleShape& getShape() const;
    void move(const sf::Vector2f& offset);
    void setPosition(const sf::Vector2f& _position);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void borderCollision(const sf::RenderWindow& window, sf::Sprite &mapSprite);
    void respawn();

private:
    sf::CircleShape shape;      // Circle shape for the player (could be changed later to something else)
    sf::Vector2f velocity;
};
