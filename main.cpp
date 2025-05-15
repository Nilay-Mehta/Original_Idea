#include <SFML/Graphics.hpp>
#include <utility>
#include "game.h"
#include "player.h"

int main() {

    // To be used for initialization of the player
    constexpr int radius = 50;
    sf::Vector2f middleOfTheScreen(Game::SCREEN_WIDTH / 2 - radius, Game::SCREEN_HEIGHT / 2 - radius);

    // Player initialized at the middle of the screen
    Player player(
        sf::CircleShape(radius),
        middleOfTheScreen,
        sf::Vector2f(0, 0)
    );

    Game game;
    game.game_loop(player);

    return 0;
}
