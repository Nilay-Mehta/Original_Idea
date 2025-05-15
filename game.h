//
// Created by nilay on 15-05-2025.
//
#pragma once

#include <SFML/Graphics.hpp>
#include "player.h"
#include <SFML/System.hpp>
#include "config.h"

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
};