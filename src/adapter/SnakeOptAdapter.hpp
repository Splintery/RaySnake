#ifndef SNAKEOPTADAPTER_H
#define SNAKEOPTADAPTER_H

#include "Adapter.hpp"
#include "../model/SnakeOpt.hpp"

class SnakeOptAdapter: public Adapter {
private:
    sf::RectangleShape *adaptPart(SnakeOptPart *);
public:
    SnakeOptAdapter(Controller *);
    
    std::vector<sf::Drawable *> adapt(Adaptable *);
};

#endif