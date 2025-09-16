#ifndef SNAKE_H
#define SNAKE_H

#include <stack>
#include "SnakePart.h"
#include "../tools/Bound.h"
#include "../tools/Direction.h"
#include "../../adapter/Adaptable.h"

class Snake: public Adaptable {
private:
    SnakePart *head;
    SnakePart *tail;
    Direction newDir;
    Direction oldDir;
    float length;

    float width = 1;
    float speed = 1;

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

    Bound predictHeadPlacement(Direction);
    virtual std::vector<Bound> getBounds();
    virtual std::vector<Direction> getDirections();

    friend std::ostream &operator<<(std::ostream &, const Snake &);
};

#endif