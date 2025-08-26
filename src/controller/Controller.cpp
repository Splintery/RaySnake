#include <iostream>
#include "Controller.h"
#include "../view/state/SplashState.h"
#include "../model/Direction.h"
#include "../model/terrain/World.h"
#include "../settings/Settings.h"

Controller::Controller(unsigned int width, unsigned int height, const std::string &title) {
    std::cout << "Creating controller..." << std::endl;

    resourceManager = new ResourceManager();
    stateMachine = new StateMachine();
    window = new sf::RenderWindow(sf::VideoMode({width, height}), title, sf::Style::Close);

    clock = sf::Clock();

    loadAssets();
    stateMachine->addState(new SplashState(this));

    run();
}

void Controller::loadAssets() {
    resourceManager->loadFont("minecraft", "./resources/Minecraft.ttf");
    resourceManager->loadBundle("snake_body_bundle", "./resources/snake_body_sheet.png", 1, 4, 16, 16);
    resourceManager->loadBundle("snake_curved_body_bundle", "./resources/snake_curved_body_sheet.png", 1, 4, 16, 16);
    resourceManager->loadBundle("snake_tail_bundle", "./resources/snake_tail_sheet.png", 1, 4, 16, 16);
    resourceManager->loadBundle("snake_animated_head", "./resources/animated_snake_head.png", 4, 1, 16, 112);
}

void Controller::draw(const sf::Drawable &drawable) {
    window->draw(drawable);
}

long Controller::getCurrentTime() {
    return clock.getElapsedTime().asMicroseconds();
};

sf::Vector2<float> Controller::getWindowCenter() {
    sf::Vector2<float> center(window->getSize().x / 2, window->getSize().y / 2);
    return center;
}
sf::Vector2<float> Controller::getMousePos() {
    return sf::Vector2<float>(sf::Mouse::getPosition(*window));
}

void Controller::gameover() {
    // window->close();
}

void Controller::run()
{
    int updates = 0;
    float updateTracker = 0.0f;

    int frames = 0;
    float frameTracker = 0.0f;

    long lastCheck = clock.getElapsedTime().asMilliseconds();
    long previousTime = clock.getElapsedTime().asMicroseconds();

    while (window->isOpen()) {
        stateMachine->processStateChanges();

        updateTracker += static_cast<float>(getCurrentTime() - previousTime) / timePerUpdate;
        if (updateTracker >= 1.0f) {
            if (!stateMachine->getActiveState()->isPaused) {
                stateMachine->getActiveState()->handleInput();
                stateMachine->getActiveState()->update();
                updates++;
            }
            updateTracker--;
        }
        frameTracker += static_cast<float>(getCurrentTime() - previousTime) / timePerFrame;
        if (frameTracker >= 1.0f) {
            stateMachine->getActiveState()->draw();

            frames++;
            frameTracker--;
        }

        if (clock.getElapsedTime().asMilliseconds() - lastCheck >= 1000) {
            lastCheck = clock.getElapsedTime().asMilliseconds();
            //            cout << "FPS: " << frames << "\nUPS: " << updates << endl;
            updates = 0;
            frames = 0;
        }
        previousTime = getCurrentTime();
    }
}
