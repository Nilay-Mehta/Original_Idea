#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <stdexcept>

class ResourceManager {
public:
    static sf::Texture& getTexture(const std::string& filename);
    static sf::Font& getFont(const std::string& filename);
    static void cleanup();

private:
    ResourceManager() = delete;

    static std::unordered_map<std::string, sf::Texture> textures;
    static std::unordered_map<std::string, sf::Font> fonts;
};