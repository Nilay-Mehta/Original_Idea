//
// Created by nilay on 15-05-2025.
//
#include <cmath>
#include <iostream>
#include <filesystem>

#include "resource_manager.h"
#include "game.h"
#include "player.h"
#include "config.h"
#include "first_projectile.h"
#include "second_projectile.h"

Game::Game()
    : window(sf::VideoMode(Config::Display::SCREEN_WIDTH, Config::Display::SCREEN_HEIGHT), "SFML TEST", sf::Style::Default),
      player(sf::Color::Blue),
      npc({0.f, 0.f}),
      currentGameState(GameState::Playing)
{
    try {
        // Load font using ResourceManager
        font = ResourceManager::getFont("assets/texts/OpenSans-Regular.ttf");
        fpsText.setFont(font);
        fpsText.setCharacterSize(18);
        fpsText.setFillColor(sf::Color::Green);
        fpsText.setPosition(10.f, 5.f);
        fpsText.setString("FPS: ");

        // Load background texture using ResourceManager
        mapTexture = ResourceManager::getTexture("assets/textures/background.jpg");
        mapSprite.setTexture(mapTexture);
    } catch (const std::exception& e) {
        std::cerr << "Asset loading error: " << e.what() << std::endl;
        window.close();  // optional: prevent game loop from starting
        throw;           // propagate to main()
    }

    // Creating the view (camera)
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(player.getPosition().x, player.getPosition().y);

    FPSDelayClock.restart();
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
        if (playerAlive) {
            if (toggle)
                projectiles.emplace_back(std::make_unique<CirBullet>(playerPos, direction));
            else
                projectiles.emplace_back(std::make_unique<CapBullet>(playerPos, direction));
        }

        toggle = !toggle;
        shootClock.restart();
    }
}

void Game::update(float deltaTime, bool updateFPS) {
    if (updateFPS) {
        float fps = 1.f / deltaTime;
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
    }

    if (!playerAlive) return;

    player.borderCollision(window, mapSprite);

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
        }else if ((*it)->isOffScreen(window, mapSprite)) {
            it = projectiles.erase(it);
        }else {
            ++it;
        }
    }

    // Check collision between NPC and player
    if (npc.isAlive() && playerAlive &&
        npc.getBounds().intersects(player.getShape().getGlobalBounds())) {
        playerAlive = false;
        currentGameState = GameState::GameOver;
        projectiles.clear();
        }
}


void Game::render() {//to render
    sf::Vector2f center = player.getPosition();
    sf::Vector2f halfSize = view.getSize() / 2.f;

    float leftBound = halfSize.x;
    float rightBound = mapSprite.getGlobalBounds().width - halfSize.x;
    float topBound = halfSize.y;
    float bottomBound = mapSprite.getGlobalBounds().height - halfSize.y;

    center.x = std::clamp(center.x, leftBound, rightBound);
    center.y = std::clamp(center.y, topBound, bottomBound);

    view.setCenter(center);
    window.setView(view);
    window.draw(mapSprite);

    if (playerAlive)
        window.draw(player.getShape());
    for (const auto& projectile : projectiles) {
        projectile->draw(window);
    }
    npc.draw(window);
    fpsText.setPosition(center - sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2) );
    window.draw(fpsText);
    if (currentGameState == GameState::Paused) {
        sf::Text pausedText("PAUSED", font, 69);
        pausedText.setFillColor(sf::Color::Green);
        pausedText.setPosition(center.x - 500, center.y - 300);
        window.draw(pausedText);
    }
    if (currentGameState == GameState::GameOver) {
        sf::Text gameOverText("GAME OVER\nPress R to Respawn", font, 69);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(center.x - 500, center.y - 300);
        window.draw(gameOverText);
    }
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
    bool updateFPS;

    // Run the program as long as the window is open
    while (window.isOpen()) {
        // Process events
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (currentGameState == GameState::Playing)
                        currentGameState = GameState::Paused;
                    else if (currentGameState == GameState::Paused)
                        currentGameState = GameState::Playing;
                }
                if (event.key.code == sf::Keyboard::R) {
                    if (currentGameState == GameState::GameOver) {
                        player.respawn();
                        playerAlive = true;
                        npc.reset();
                        currentGameState = GameState::Playing;
                    } else if (currentGameState == GameState::Paused) {
                        npc.reset();
                    }
                }
            }
        }

        // Calculate delta time as (time of current frame - time of prev frame)
        const sf::Time currentTime = clock.getElapsedTime();
        float deltaTime = (currentTime - lastTime).asSeconds();
        lastTime = currentTime;

        // Prevent delta time from getting too big
        if (deltaTime > Config::Timing::MAX_DELTA_TIME)
            deltaTime = Config::Timing::MAX_DELTA_TIME;

        if (FPSDelayClock.getElapsedTime().asMilliseconds() > 500) {
            FPSDelayClock.restart();
            updateFPS = true;
        } else {
            updateFPS = false;
        }

        if (currentGameState == GameState::Playing) {
            handleInput(deltaTime);
            update(deltaTime, updateFPS);
        }

        render();
    }
}
