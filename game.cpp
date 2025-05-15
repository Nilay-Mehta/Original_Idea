//
// Created by nilay on 15-05-2025.
//
#include "game.h"
#include "player.h"
Game::Game()
    :window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML TEST"),
    player(
        sf::CircleShape(Player::radius),
        Player::middleOfTheScreen(),
        sf::Vector2f(0.0f, 0.0f)
    )
{}

void Game::game_loop() {
    // Run the program as long as the window is open
    while (window.isOpen()) {
        // Process events
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the screen
        window.clear(sf::Color::Black);

        // Draw the player
        window.draw(player.getShape());

        // Display the contents of the window
        window.display();
    }

}

void Game::draw() {
}
