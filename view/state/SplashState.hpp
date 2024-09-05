#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include "../State.hpp"
#include "../../controller/Controller.hpp"

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
    Controller *controller;
    sf::Text gameTitle;
    int sizeIncrement;
};

#endif