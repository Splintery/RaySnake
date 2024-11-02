#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "Direction.hpp"
#include "Snake.hpp"

class World {
private:
    Bound bounds;
    Snake *snake;
public:
    bool gameover = false;
    World(Bound bounds, Snake *Snake);
    void update();
    int getWidth();
    int getHeight();
};

#endif