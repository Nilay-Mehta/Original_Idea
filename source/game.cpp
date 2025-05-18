//
// Created by nilay on 15-05-2025.
//
#include <cmath>
#include <iostream>
#include <filesystem>

#include "../include/game.h"
#include "../include/player.h"
#include "../include/config.h"
#include "../include/first_projectile.h"
#include "../include/second_projectile.h"

Game::Game()
    :window(sf::VideoMode(Config::Display::SCREEN_WIDTH, Config::Display::SCREEN_HEIGHT), "SFML TEST", sf::Style::Default),
    player(sf::Color::Blue),
    npc({0.f, 0.f})
{
    std::filesystem::path exeDir = std::filesystem::current_path();
    std::filesystem::path fontPath = exeDir.parent_path() / "text" / "OpenSans-Regular.ttf";
    if (!font.loadFromFile(fontPath.string())) {
        std::cerr << "Failed to load font from: " << fontPath << std::endl;
    }

    fpsText.setFont(font);
    fpsText.setCharacterSize(18);
    fpsText.setFillColor(sf::Color::Green);
    fpsText.setPosition(10.f, 5.f);
    fpsText.setString("FPS: ");
}

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

    // std::cout << "Checking mouse input...\n";
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootClock.getElapsedTime().asMilliseconds() > 150) {

        // std::cout << "Projectile fired!\n";

        sf::Vector2f playerPos = player.getPosition();
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);
        sf::Vector2f direction = worldMousePos - playerPos;

        // Alternate between Circle and Capsule projectiles
        static bool toggle = false;
        if (toggle)
            projectiles.emplace_back(std::make_unique<CirBullet>(playerPos, direction));
        else
            projectiles.emplace_back(std::make_unique<CapBullet>(playerPos, direction));

        toggle = !toggle;
        shootClock.restart();
    }
}

void Game::update(float deltaTime) {
    float fps = 1.f / deltaTime;
    fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));

    if (!playerAlive) return;

    player.borderCollision(window);

    // Always update all projectiles movement
    for (auto& p : projectiles) {
        p->update(deltaTime);
    }

    npc.update(deltaTime, player.getPosition(), Config::Player::PLAYER_SPEED * 0.6f);

    // Then handle collisions & erasing projectiles
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {

        if (npc.isAlive() && npc.getBounds().intersects((*it)->getBounds())) {
            npc.kill();
            it = projectiles.erase(it);
        }else if ((*it)->isOffScreen(window)) {
            it = projectiles.erase(it);
        }else {
            ++it;
        }
    }

    // Check collision between NPC and player
    if (npc.isAlive() && playerAlive &&
        npc.getBounds().intersects(player.getShape().getGlobalBounds())) {
        playerAlive = false;
        projectiles.clear();
        }
}


void Game::render() {//to render
    window.clear(sf::Color::Black);

    if (playerAlive)
        window.draw(player.getShape());
    for (const auto& projectile : projectiles) {
        projectile->draw(window);
    }
    npc.draw(window);
    window.draw(fpsText);
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
