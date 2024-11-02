#ifndef SNAKEADAPTER_H
#define SNAKEADAPTER_H

#include "Adapter.hpp"
#include "../model/Snake.hpp"

class SnakeAdapter: public Adapter {
private:
    sf::Sprite *getHeadTexture(SnakePart *);
    sf::Sprite *getTailTexture(SnakePart *);
    sf::Sprite *getBodyTexture(SnakePart *);
    sf::Sprite *getBentBodyTexture(SnakePart *);

    sf::Sprite *adaptPart(SnakePart *);
public:
    SnakeAdapter(Controller *);
    
    std::vector<sf::Drawable *> adapt(Adaptable *);
};

#endif