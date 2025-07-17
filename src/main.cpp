#include <iostream>
#include "game.h"

int main() {
    try {
        Game game;
        game.game_loop();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        // Optional: show popup dialog here or just console message
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
