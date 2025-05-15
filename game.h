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
    void ini_window();
    void game_loop();
    void update();
    void draw();

private:
    sf::RenderWindow window;
    Player player;
};