#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "Direction.hpp"
#include "Snake.hpp"
#include "SnakeOpt.hpp"

class World {
private:
    sf::IntRect bounds;
public:
    bool gameover = false;
    SnakeOpt *snake;
    World(sf::IntRect bounds, Direction startDir);
    void update();
    SnakeOpt &getSnake();
    int getWidth();
    int getHeight();
};

#endif