#include <iostream>
#include <cmath>
#include "SnakeAdapter.hpp"

using namespace sf;

Adapter::~Adapter() { std::cout << "Destroyed adapter" << std::endl; }
Adapter::Adapter(Controller *ctrl): ctrl{ctrl} {}
SnakeAdapter::SnakeAdapter(Controller *ctrl, const Direction &d, sf::Vector2f pos, float size): Adapter{ctrl}, Snake{d, pos, size} {
    for (SnakePart *p = head; p != nullptr; p = p->getNext()) {
        
    }
}

void SnakeAdapter::updateView() {
    
}

void SnakeAdapter::draw(sf::RenderTarget &target, sf::RenderStates states) const {}

void SnakeAdapter::update() {
    Snake::update();
}

void SnakeAdapter::grow(float amount) {
    Snake::grow(amount);
}

void SnakeAdapter::move(float amount) {
    Snake::move(amount);
}
