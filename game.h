//
// Created by nilay on 15-05-2025.
//
#pragma once

#include <SFML/Graphics.hpp>
#include "player.h"
#include <SFML/System.hpp>

class Game {
public:
    static constexpr uint16_t SCREEN_WIDTH = 1200;
    static constexpr uint16_t SCREEN_HEIGHT = 800;

    Game();
    void ini_window();
    void game_loop(Player& player);
    void update();
    void draw();

private:
    sf::RenderWindow window;
};