#ifndef SNAKE_H
#define SNAKE_H

#include "SnakePart.hpp"
#include "Direction.hpp"

class Snake {
protected:
    SnakePart *head;
    SnakePart *tail;
    Direction newDir;
    Direction oldDir;
    float length;
    float speed = 0.1f;

    void trimTail();
    void glueHead();
public:
    Snake(const Direction &, sf::Vector2f, float);
    virtual ~Snake();
    Snake(const Snake &) = delete;
    virtual void update();
    float size();
    virtual void grow(float);
    virtual void move(float);
    void setDirection(const Direction &);
    SnakePart *getHead();
    SnakePart *getTail();

    friend std::ostream &operator<<(std::ostream &, const Snake &);
};

#endif