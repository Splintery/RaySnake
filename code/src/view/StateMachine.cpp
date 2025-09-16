#include <iostream>
#include "StateMachine.h"
#include "../model/tools/ObjectTracker.h"

StateMachine::StateMachine() {
    std::cout << "Constructed state machine." << std::endl;
    ObjectTracker::addTo("StateMachine");
}

StateMachine::~StateMachine() {
    while (!states.empty()) {
        delete(states.top());
        states.pop();
    }
    ObjectTracker::removeFrom("StateMachine");
}

void StateMachine::addState(State *newState, bool isReplacing) {
    this -> isAdding = true;
    this -> isReplacing = isReplacing;
    this -> newState = std::move(newState);
}
void StateMachine::removeState() {
    isRemoving = true;
}

void StateMachine::removeBackendState() {
    isRemovingBackend = true;
}

void StateMachine::processStateChanges() {
    if (isRemoving && !states.empty()) {
        delete(states.top());
        states.pop();
        if (!states.empty()) {
            states.top() -> resume();
        }

        isRemoving = false;
    }
    if (isAdding) {
        if (!states.empty()) {
            if (isReplacing) {
                delete(states.top());
                states.pop();
            } else {
                states.top() -> pause();
            }
        }

        states.push(std::move(newState));
        states.top() -> init();
        isAdding = false;
    }
    if (isRemovingBackend) {
        if (!states.empty()) {
            State *stateToKeep = std::move(states.top());
            stateToKeep -> pause();
            states.pop();
            while (!states.empty()) {
                delete(states.top());
                states.pop();
            }
            states.push(std::move(stateToKeep));
            states.top() -> resume();
        }
        isRemovingBackend = false;
    }
}

State *StateMachine::getActiveState() {
    return states.top();
}