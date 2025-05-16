//
// Created by nilay on 15-05-2025.
//
#include <cmath>
#include <iostream>

#include "game.h"
#include "player.h"
#include "config.h"

Game::Game()
    :window(sf::VideoMode(Config::Display::SCREEN_WIDTH, Config::Display::SCREEN_HEIGHT), "SFML TEST", sf::Style::Default),
    player(sf::Color::Blue)
{}

void Game::handleInput(const float deltaTime) { //user inputs for movement
    sf::Vector2f direction(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction.x -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction.x += 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1.0f;

    if (direction.x != 0.0f || direction.y != 0.0f) {
        const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;

        player.move(direction * Config::Player::PLAYER_SPEED * deltaTime);
    }
}

void Game::update(float deltaTime) {
    //empty for now but maksood bhai yahi p updates denge
    player.borderCollision(window);
}

void Game::render() {//to render
    window.clear(sf::Color::Black);
    window.draw(player.getShape());
    window.display();
}

void Game::game_loop() {
    // Avoid using both at the same time. Vsync recommended.
    if (Config::Display::VSYNC_ENABLED) {
        window.setVerticalSyncEnabled(true);
    }
    if (Config::Display::FRAMERATE_LIMIT_ENABLED) {
        window.setFramerateLimit(Config::Display::MAX_FPS);
    }

    sf::Clock clock;
    sf::Time lastTime = clock.getElapsedTime();

    // Run the program as long as the window is open
    while (window.isOpen()) {
        // Process events
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calculate delta time as (time of current frame - time of prev frame)
        const sf::Time currentTime = clock.getElapsedTime();
        float deltaTime = (currentTime - lastTime).asSeconds();
        lastTime = currentTime;

        // Prevent delta time from getting too big
        if (deltaTime > Config::Timing::MAX_DELTA_TIME)
            deltaTime = Config::Timing::MAX_DELTA_TIME;

        handleInput(deltaTime);
        update(deltaTime);
        render();
    }
}
