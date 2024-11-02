#ifndef SNAKEADAPTER_H
#define SNAKEADAPTER_H

#include "Adapter.hpp"
#include "../model/Snake.hpp"

class SnakeAdapter: public Adapter {
private:
    sf::RectangleShape *adaptPart(SnakePart *);
public:
    SnakeAdapter(Controller *);
    
    std::vector<sf::Drawable *> adapt(Adaptable *);
};

#endif