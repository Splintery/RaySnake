#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "Direction.hpp"
#include "Snake.hpp"

class World {
private:
    sf::IntRect bounds;
public:
    bool gameover = false;
    Snake *snake;
    World(sf::IntRect bounds, Direction startDir);
    void update();
    Snake &getSnake();
    int getWidth();
    int getHeight();
};

#endif