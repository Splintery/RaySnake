#ifndef SNAKEOPT_H
#define SNAKEOPT_H

#include <stack>
#include "SnakeOptPart.hpp"
#include "Direction.hpp"
#include "../adapter/Adaptable.hpp"

class SnakeOpt: public Adaptable {
private:
    SnakeOptPart *head;
    SnakeOptPart *tail;
    Direction dir;
    Direction oldDir;
    float length;

    void trimTail();
    void glueHead();
public:
    SnakeOpt(const Direction &, sf::Vector2f, float);
    void update();
    float size();
    void grow(float);
    void move(float);
    void setDirection(const Direction &);
    SnakeOptPart *getHead();
    SnakeOptPart *getTail();

    friend std::ostream &operator<<(std::ostream &, const SnakeOpt &);
};

#endif