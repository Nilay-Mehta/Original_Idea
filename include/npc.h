#pragma once

#include <SFML/Graphics.hpp>

class NPC {
public:
    explicit NPC(const sf::Vector2f& position);

    void update(float deltaTime, const sf::Vector2f& playerPos, float sqSpeed);
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    bool isAlive() const;
    void kill();
    void reset();

private:
    sf::RectangleShape shape;
    bool alive = true;
};
