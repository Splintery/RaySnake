#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include "../view/ResourceManager.hpp"
#include "../view/StateMachine.hpp"
#include "../model/terrain/World.hpp"

class Controller {
    sf::Clock clock;
    int UPS = 100;
    int FPS = 144;
    const float timePerUpdate = 1000000.0f / static_cast<float>(UPS);
    const float timePerFrame = 1000000.0f / static_cast<float>(FPS);

public:
    ResourceManager* resourceManager;
    StateMachine* stateMachine;
    sf::RenderWindow* window;
    Snake *snake;

    Controller(int width, int height, const std::string &title);

    void loadAssets();

    long getCurrentTime();
    sf::Vector2f getWindowCenter();
    sf::Vector2f getMousePos();
    void draw(const sf::Drawable &drawable);


    void gameover();
    void run();
    void moveTmp();
};

#endif