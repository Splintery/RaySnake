#ifndef SNAKE_H
#define SNAKE_H

#include <stack>
#include "SnakePart.hpp"
#include "Direction.hpp"
#include "../adapter/Adaptable.hpp"

class Snake: public Adaptable {
private:
    SnakePart *head;
    SnakePart *tail;
    Direction dir;
    int size;
public:
    Snake(const Direction &, sf::Vector2f position);
    void update();
    void grow(int n);
    void move();
    void setDirection(const Direction &);
    sf::Vector2f getHeadPosition();
    SnakePart *getHead();
    SnakePart *getTail();
};

#endif