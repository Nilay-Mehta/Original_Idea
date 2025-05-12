#include <SFML/Graphics.hpp>
#include <utility>

constexpr uint16_t SCREEN_WIDTH = 800;
constexpr uint16_t SCREEN_HEIGHT = 600;

// Defining the player class
class Player {
    // Get a circle shape for the player (should be changed later)
    sf::CircleShape shape;
    sf::Vector2f velocity;

public:
    // Constructor that takes the shape, position, velocity
    Player(sf::CircleShape  _shape, const sf::Vector2f position, const sf::Vector2f& _velocity) :
    shape(std::move(_shape)), velocity(_velocity) { shape.setPosition(position.x, position.y); }

    // Set position using a vector
    void setPosition(const sf::Vector2f& _position) {
        shape.setPosition(_position.x, _position.y);
    }

    // Set position using x and y coordinates
    void setPosition(const float& _x, const float& _y) {
        shape.setPosition(_x, _y);
    }

    // Get position as a vector
    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

    // Set velocity using a vector
    void setVelocity(const sf::Vector2f& _velocity) {
        velocity = _velocity;
    }

    // Set velocity using x and y coordinates
    void setVelocity(const float& _x, const float& _y) {
        velocity.x = _x;
        velocity.y = _y;
    }

    // Get velocity as a vector
    sf::Vector2f getVelocity() const {
        return velocity;
    }

    // Set the color of the player
    void setFillColor(const sf::Color& _color) {
        shape.setFillColor(_color);
    }

    // Get shape (read only)
    const sf::CircleShape& getShape() const {
        return shape;
    }

    // Update the position of the player
    void update() {
        shape.setPosition(shape.getPosition() + velocity);
    }
};

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
