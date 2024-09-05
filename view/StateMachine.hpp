#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <stack>
//#include <SFML/Graphics.hpp>
#include "State.hpp"

class StateMachine {
public:
    StateMachine();
    virtual ~StateMachine();

    StateMachine(const StateMachine&) = delete;
    StateMachine& operator=(const StateMachine&) = delete;

    void addState(State *newState, bool isReplacing = true);
    void removeState();
    void removeBackendState();
    void processStateChanges();
    State *getActiveState();

private:
    std::stack<State *> states;
    State *newState;

    bool isRemoving = false;
    bool isAdding = false;
    bool isReplacing = false;
    bool isRemovingBackend = false;
};



#endif
