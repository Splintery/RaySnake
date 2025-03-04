#ifndef SNAKEADAPTER_H
#define SNAKEADAPTER_H

#include "Adapter.hpp"
#include "../model/Snake.hpp"

class SnakeAdapter: public Adapter {
private:
    sf::Texture getHeadTexture(SnakePart *);
    sf::Texture getCurvedBodyTexture(SnakePart *);
    sf::Texture getBodyTexture(SnakePart *);
    sf::Texture getTailTexture(SnakePart *);
    sf::Texture findTexture(SnakePart *, float i);
    sf::Drawable *adaptPart(SnakePart *);
public:
    SnakeAdapter(Controller *);
    
    std::vector<sf::Drawable *> adapt(Adaptable *);
};

#endif