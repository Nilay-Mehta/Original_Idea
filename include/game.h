//
// Created by nilay on 15-05-2025.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "player.h"
#include "npc.h"
#include "base_projectile.h"

enum class GameState {
    Playing,
    Paused,
    GameOver
};

class Game {
public:
    Game();
    void game_loop();

private:
    void handleInput(float deltaTime);
    void update(float deltaTime);
    void render();

    sf::RenderWindow window;
    GameState currentGameState;
    Player player;
    bool playerAlive = true;
    NPC npc;
    std::vector<std::unique_ptr<BaseProjectile>> projectiles;
    sf::Clock shootClock;
    sf::Font font;
    sf::Text fpsText;
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
    sf::View view;
};