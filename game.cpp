//
// Created by nilay on 15-05-2025.
//
#include <stdio.h>
#include "game.h"

#include <cmath>
#include <iostream>

#include "player.h"
Game::Game()
    :window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML TEST", sf::Style::Default),
    player(sf::Color::Blue)
{}

void Game::handleInput(float deltaTime) {//user inputs for movement
    sf::Vector2f direction(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction.x -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction.x += 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1.0f;

    if (direction.x != 0.0f || direction.y != 0.0f) {
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;

        const float speed = 150.0f;
        player.move(direction * speed * deltaTime);
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

    sf::Clock clock;
    // Run the program as long as the window is open
    while (window.isOpen()) {
        // Process events
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        handleInput(deltaTime);
        update(deltaTime);
        render();
    }
}
