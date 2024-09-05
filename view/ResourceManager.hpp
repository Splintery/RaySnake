#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <SFML/Graphics.hpp>

class ResourceManager {
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
public:
    ResourceManager();
    virtual ~ResourceManager() = default;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    sf::Texture &getTexture(std::string key);
    void loadTexture(std::string key, std::string filePath);

    void loadFont(std::string key, std::string filePath);
    sf::Font &getFont(std::string key);
};

#endif