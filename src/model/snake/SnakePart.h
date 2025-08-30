#ifndef SNAKEPART_H
#define SNAKEPART_H

#include <SFML/Graphics.hpp>
#include "../Direction.h"
#include "../Bound.h"

class SnakePart {
private:
    sf::Texture currentTexture;
    SnakePart *prev;
    SnakePart *next;
    Direction dir;

    Bound *bounds;
public:
    SnakePart(SnakePart *, SnakePart *, Direction dir, Bound *bounds);
    virtual ~SnakePart();
    SnakePart(const SnakePart &) = delete;
    float size();
    float totalSize(float accumulator = 0);
    void grow(float, bool);
    void addNext(SnakePart *);
    void addPrev(SnakePart *);
    void removeNext();
    void removePrev();
    Direction getDir();
    SnakePart *getNext();
    SnakePart *getPrev();
    Bound *getBound();

    friend std::ostream &operator<<(std::ostream &, const SnakePart &);
};

#endif