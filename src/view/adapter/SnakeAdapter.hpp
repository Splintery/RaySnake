#ifndef SNAKE_ADAPTER_H
#define SNAKE_ADAPTER_H

#include <list>
#include "../../controller/Controller.hpp"
#include "../../model/Snake.hpp"

class SnakeAdapter {
private:
    Controller *controller;

    sf::Sprite getHeadTexture(SnakePart *);
    sf::Sprite getTailTexture(SnakePart *);
    sf::Sprite getBodyTexture(SnakePart *);
    sf::Sprite getBentBodyTexture(SnakePart *);

    sf::Sprite adaptPart(SnakePart *);
public:
    SnakeAdapter(Controller *);
    
    std::list<sf::Sprite> adaptSnake(Snake *);
};

#endif