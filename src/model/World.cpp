#include "World.hpp"

World::World(Bound bounds, Snake *snake): bounds{bounds}, snake{snake} {}

void World::update() {
    sf::Vector2f headPosition = snake->getHead()->getBounds()->topL;
    if (!bounds.contains(headPosition.x, headPosition.y)) {
        gameover = true; // threadUnsafe
    } else {
        snake->update();
    }
}

int World::getWidth() {
    return bounds.width();
}
int World::getHeight() {
    return bounds.height();
}
