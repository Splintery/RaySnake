#include "World.hpp"

World::World(sf::IntRect bounds, Direction startDir): bounds{bounds} {
    this->snake = new Snake(startDir, sf::Vector2f(0, 0));
}

void World::update() {
    sf::Vector2f headPosition = snake->getHeadPosition();
    if (!bounds.contains(headPosition.x, headPosition.y)) {
        gameover = true; // threadUnsafe
    } else {
        snake->update();
    }
}

Snake &World::getSnake() {
    return *snake;
}

int World::getWidth() {
    return bounds.width;
}
int World::getHeight() {
    return bounds.height;
}
