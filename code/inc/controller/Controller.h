#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include "../view/ResourceManager.h"
#include "../view/StateMachine.h"
#include "../model/terrain/World.h"

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

    Controller(unsigned int width, unsigned int height, const std::string &title);

    void loadAssets();

    long getCurrentTime();
    sf::Vector2<float> getWindowCenter();
    sf::Vector2<float> getMousePos();
    void draw(const sf::Drawable &drawable);


    void gameover();
    void run();
    void moveTmp();
};

#endif