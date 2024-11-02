#ifndef SNAKEPART_H
#define SNAKEPART_H

#include <SFML/Graphics.hpp>
#include "Direction.hpp"
#include "Bound.hpp"

class SnakePart {
private:
    sf::Texture currentTexture;
    SnakePart *prev;
    SnakePart *next;
    Direction dir;

    Bound *bounds;

public:
    SnakePart(SnakePart *, SnakePart *, Direction dir, Bound *bounds);
    float size(float accumulator = 0);
    void growHead(float);
    void growTail(float);
    void grow(float);
    void addNext(SnakePart *);
    void addPrev(SnakePart *);
    void removeNext();
    void removePrev();
    Direction getDirection();
    SnakePart *getNext();
    SnakePart *getPrev();
    Bound *getBounds();

    friend std::ostream &operator<<(std::ostream &, const SnakePart &);
};

#endif