#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <list>
#include "../State.hpp"
#include "../../controller/Controller.hpp"
#include "../adapter/SnakeAdapter.hpp"

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
    std::list<sf::Sprite> currentSnake;
    SnakeAdapter *adpater;
    Controller *controller;

    void drawGrid();
};

#endif