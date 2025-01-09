#include <iostream>
#include "Controller.hpp"
#include "../view/state/SplashState.hpp"
#include "../model/Direction.hpp"
#include "../model/World.hpp"
#include "../settings/Settings.hpp"

Controller::Controller(int width, int height, const std::string &title) {
    std::cout << "Creating controller..." << std::endl;

    resourceManager = new ResourceManager();
    stateMachine = new StateMachine();
    window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Close);

    clock = sf::Clock();

    loadAssets();
    snake = new Snake(Direction::East, sf::Vector2f(0, 0), 20);

    stateMachine->addState(new SplashState(this));

    run();
}

void Controller::loadAssets() {
    resourceManager->loadFont("minecraft", "./resources/Minecraft.ttf");
    resourceManager->loadTexture("snake_head", "./resources/snake_sprite.png", sf::IntRect(0, 0, 64, 256));
    resourceManager->loadTexture("snake_body", "./resources/snake_sprite.png", sf::IntRect(64, 0, 64, 128));
    resourceManager->loadTexture("snake_bent_body", "./resources/snake_sprite.png", sf::IntRect(128, 0, 64, 256));
    resourceManager->loadTexture("snake_tail", "./resources/snake_sprite.png", sf::IntRect(192, 0, 64, 256));
    resourceManager->loadTexture("tmp", "./resources/tmp_tile.png");
    resourceManager->getTexture("tmp").setRepeated(true);
    resourceManager->loadTexture("testAni", "./resources/testAnimation.png");
}

void Controller::draw(const sf::Drawable &drawable) {
    window->draw(drawable);
}

// sf::ConvexShape polygon;
// polygon.setPointCount(5);
// polygon.setPoint(0, sf::Vector2f(100, 100));
// polygon.setPoint(1, sf::Vector2f(150, 360));
// polygon.setPoint(2, sf::Vector2f(650, 400));
// polygon.setPoint(3, sf::Vector2f(605, 370));
// polygon.setPoint(4, sf::Vector2f(215, 150));
// polygon.setOutlineColor(sf::Color::Red);
// polygon.setOutlineThickness(1);

long Controller::getCurrentTime() {
    return clock.getElapsedTime().asMicroseconds();
};

sf::Vector2f Controller::getWindowCenter() {
    sf::Vector2f center(window->getSize().x / 2, window->getSize().y / 2);
    return center;
}
sf::Vector2f Controller::getMousePos() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    sf::Vector2f res(mousePos.x, mousePos.y);
    return res;
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
                snake->move(0.25);
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
