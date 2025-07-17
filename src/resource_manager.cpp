#include "resource_manager.h"
#include <iostream>

std::unordered_map<std::string, sf::Texture> ResourceManager::textures;
std::unordered_map<std::string, sf::Font> ResourceManager::fonts;

sf::Texture& ResourceManager::getTexture(const std::string& filename) {
    auto it = textures.find(filename);
    if (it != textures.end()) {
        return it->second;
    }

    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    textures[filename] = std::move(texture);
    return textures[filename];
}

sf::Font& ResourceManager::getFont(const std::string& filename) {
    auto it = fonts.find(filename);
    if (it != fonts.end()) {
        return it->second;
    }

    sf::Font font;
    if (!font.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load font: " + filename);
    }
    fonts[filename] = std::move(font);
    return fonts[filename];
}

void ResourceManager::cleanup() {
    textures.clear();
    fonts.clear();
}
