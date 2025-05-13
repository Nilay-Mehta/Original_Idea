#include <SFML/Graphics.hpp>
#include <utility>
#include "player.h"

constexpr uint16_t SCREEN_WIDTH = 800;
constexpr uint16_t SCREEN_HEIGHT = 600;

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Test");

    // To be used for initialization of the player
    constexpr int radius = 50;
    sf::Vector2f middleOfTheScreen(SCREEN_WIDTH / 2 - radius, SCREEN_HEIGHT / 2 - radius);

    // Player initialized at the middle of the screen
    Player player(
        sf::CircleShape(radius),
        middleOfTheScreen,
        sf::Vector2f(0, 0)
    );

    // Player is red
    player.setFillColor(sf::Color::Red);

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

    return 0;
}
