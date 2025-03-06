#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <list>
#include "../State.hpp"
#include "../../controller/Controller.hpp"
#include "../../adapter/SnakeAdapter.hpp"
#include "../AnimatedSprite.hpp"

class SplashState: public State {
public:
    SplashState(Controller *);
    virtual ~SplashState();
    SplashState(const SplashState &) = delete;
    SplashState operator=(const SplashState) = delete;

    void init();
    void handleInput();
    void update();
    void draw();
    void setSnake(std::stack<SnakePart *> newSnake);
private:
    Snake *snake;
    std::vector<sf::Drawable *> currentSpriteSnake;
    SnakeAdapter *adpater;
    Controller *controller;
    bool moving = false;

    AnimatedSprite *an;
};

#endif