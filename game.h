//
// Created by nilay on 15-05-2025.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "player.h"
#include "inv.h"
#include "npc.h"

class Game {
public:
    Game();
    void game_loop();

private:
    void handleInput(float deltaTime);
    void update(float deltaTime);
    void render();

    sf::RenderWindow window;
    Player player;
    bool playerAlive = true;
    NPC npc;
    std::vector<Projectile> projectiles;
    sf::Clock shootClock;
};