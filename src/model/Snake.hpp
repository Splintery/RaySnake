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
    Direction newDir;
    Direction oldDir;
    float length;

    void trimTail();
    void glueHead();
public:
    Snake(const Direction &, sf::Vector2f, float);
    virtual ~Snake();
    Snake(const Snake &) = delete;
    void update();
    float size();
    void grow(float);
    void move(float);
    void setDirection(const Direction &);
    SnakePart *getHead();
    SnakePart *getTail();

    friend std::ostream &operator<<(std::ostream &, const Snake &);
};

#endif