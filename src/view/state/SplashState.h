#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <list>
#include "../State.hpp"
#include "../../controller/Controller.h"
#include "../../adapter/SnakeAdapter.h"
#include "../AnimatedSprite.h"

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
private:
    Snake *snake;
    SnakeAdapter *drawableSnake;
    Controller *controller;
    bool moving = false;

    AnimatedSprite *an;
};

#endif