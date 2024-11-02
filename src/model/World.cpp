#include "World.hpp"

World::World(sf::IntRect bounds, Direction startDir): bounds{bounds} {
    this->snake = new SnakeOpt(startDir, sf::Vector2f(0, 0), 2.0f);
}

void World::update() {
    sf::Vector2f headPosition = snake->getHead()->getBounds()->topL;
    if (!bounds.contains(headPosition.x, headPosition.y)) {
        gameover = true; // threadUnsafe
    } else {
        snake->update();
    }
}

SnakeOpt &World::getSnake() {
    return *snake;
}

int World::getWidth() {
    return bounds.width;
}
int World::getHeight() {
    return bounds.height;
}
