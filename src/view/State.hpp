#ifndef STATE_H
#define STATE_H

#include <ostream>
#include <iostream>

class State {
public:
    State() {
        std::cout << "state created." << std::endl;
    }
    virtual ~State() {
        std::cout << "state destroyed." << std::endl;
    }

    virtual void init() = 0;
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void pause() {}
    virtual void resume() {}

    bool isPaused = false;
};

#endif
