#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <SFML/Graphics.hpp>

class ResourceManager {
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
    std::map<std::string, std::vector<sf::Texture>> bundles;
public:
    ResourceManager();
    virtual ~ResourceManager() = default;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    sf::Texture &getTexture(std::string key);
    void loadTexture(std::string key, std::string filePath, sf::IntRect area = sf::IntRect());

    void loadFont(std::string key, std::string filePath);
    sf::Font &getFont(std::string key);

    void loadBundle(std::string key, std::vector<std::string> filePaths);
    // linesize && columnsize must be expressed in pixels
    void loadBundle(std::string key, std::string filePath, int line, int column, int linesize, int colsize);
    void loadBundle(std::string key, std::vector<sf::Texture> textures);
    std::vector<sf::Texture> &getBundle(std::string key);
};

#endif