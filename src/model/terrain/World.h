#ifndef WORLD_H
#define WORLD_H

#include <set>
#include <SFML/Graphics.hpp>
#include "../Direction.h"
#include "../snake/Snake.h"


class World {
private:
    std::set<Bound> bounds;
public:
    bool gameover = false;
    World();
    void update();
};

#endif