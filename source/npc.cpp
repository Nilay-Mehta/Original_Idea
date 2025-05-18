#include "../include/npc.h"
#include <cmath>

NPC::NPC(const sf::Vector2f& position) {
    shape.setSize({50.f, 50.f});
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(25.f, 25.f);
    shape.setPosition(position);
}

void NPC::update(float deltaTime, const sf::Vector2f& playerPos, float NPCSpeed) {
    if (!alive) return;

    sf::Vector2f direction = playerPos - shape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;
        shape.move(direction * NPCSpeed * deltaTime);
    }
}

void NPC::draw(sf::RenderWindow& window) const {
    if (alive)
        window.draw(shape);
}

sf::FloatRect NPC::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f NPC::getPosition() const {
    return shape.getPosition();
}

bool NPC::isAlive() const {
    return alive;
}

void NPC::kill() {
    alive = false;
}
