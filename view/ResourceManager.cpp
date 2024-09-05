#include <iostream>
#include "ResourceManager.hpp"

ResourceManager::ResourceManager() {
    std::cout << "Constructed resource manager." << std::endl;
}

void ResourceManager::loadTexture(std::string key, std::string filePath) {
    sf::Texture texture;

    if (texture.loadFromFile(filePath)) {
        this -> textures[key] = texture;
    }
}
sf::Texture &ResourceManager::getTexture(std::string key) {
    return this -> textures.at(key);
}

void ResourceManager::loadFont(std::string key, std::string filePath) {
    sf::Font font;

    if (font.loadFromFile(filePath)) {
        this -> fonts[key] = font;
    }
}
sf::Font &ResourceManager::getFont(std::string key) {
    return this -> fonts.at(key);
}
