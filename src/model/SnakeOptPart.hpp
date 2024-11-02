#ifndef SNAKEOPTPART_H
#define SNAKEOPTPART_H

#include <SFML/Graphics.hpp>
#include "Direction.hpp"
#include "Bound.hpp"

class SnakeOptPart {
private:
    sf::Texture currentTexture;
    SnakeOptPart *prev;
    SnakeOptPart *next;
    Direction dir;

    Bound *bounds;

public:
    SnakeOptPart(SnakeOptPart *, SnakeOptPart *, Direction dir, Bound *bounds);
    float size(float accumulator = 0);
    void growHead(float);
    void growTail(float);
    void grow(float);
    void addNext(SnakeOptPart *);
    void addPrev(SnakeOptPart *);
    void removeNext();
    void removePrev();
    Direction getDirection();
    SnakeOptPart *getNext();
    SnakeOptPart *getPrev();
    Bound *getBounds();

    friend std::ostream &operator<<(std::ostream &, const SnakeOptPart &);
};

#endif