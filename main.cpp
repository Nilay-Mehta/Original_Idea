#include <SFML/Graphics.hpp>

int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");

    // Create a red circle
    sf::CircleShape shape(50);  // Radius of 50 pixels
    shape.setFillColor(sf::Color::Red);

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the screen
        window.clear(sf::Color::Black);

        // Draw the circle
        window.draw(shape);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
