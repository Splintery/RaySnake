#include <iostream>
#include "ResourceManager.hpp"

ResourceManager::ResourceManager() {
    std::cout << "Constructed resource manager." << std::endl;
}

void ResourceManager::loadTexture(std::string key, std::string filePath, sf::IntRect area) {
    sf::Texture texture;

    if (texture.loadFromFile(filePath, area)) {
        this->textures[key] = texture;
    }
}

sf::Texture &ResourceManager::getTexture(std::string key) {
    return this->textures.at(key);
}

std::vector<sf::Texture> ResourceManager::cutTexture(std::string key, int line, int column, int linesize, int colsize) {
    sf::Image cutme = getTexture(key).copyToImage();
    std::vector<sf::Texture> textures(line * column, getTexture(key));

    for (int l = 0; l < line; l++) {
        for (int c = 0; c < column; c++) {
            textures
            .at(line * linesize * l + c)
            .loadFromImage(cutme, sf::IntRect(c * colsize, l * linesize, colsize, linesize));
        }
    }
    return textures;
}

void ResourceManager::loadFont(std::string key, std::string filePath) {
    sf::Font font;

    if (font.loadFromFile(filePath)) {
        this->fonts[key] = font;
    }
}
sf::Font &ResourceManager::getFont(std::string key) {
    return this->fonts.at(key);
}

void ResourceManager::loadBundle(std::string key, std::vector<std::string> filePaths) {
    std::vector<sf::Texture> b;
    for (size_t i = 0; i < filePaths.size(); i++) {
        sf::Texture t;
        if (t.loadFromFile(filePaths.at(i))) {
            b.push_back(t);
        }
    }
    this->bundles[key] = b;
}

void ResourceManager::loadBundle(std::string key, std::vector<sf::Texture> textures) {
    this->bundles[key] = textures;
}

std::vector<sf::Texture> &ResourceManager::getBundle(std::string key) {
    return this->bundles.at(key);
}
