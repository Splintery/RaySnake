#ifndef SNAKEPART_H
#define SNAKEPART_H

#include <SFML/Graphics.hpp>
#include "Direction.hpp"

class SnakePart {
private:
    sf::Texture currentTexture;
    SnakePart *prev;
    SnakePart *next;
    Direction dir;

    sf::Vector2f position;

public:
    SnakePart(SnakePart *, SnakePart *, Direction dir, sf::Vector2f position);
    void move();
    void addNext(SnakePart *);
    void addPrev(SnakePart *);
    void setDirection(const Direction &);
    Direction getDirection();
    sf::Vector2f getPosition();
    sf::Vector2f getNextPosition();
    SnakePart *getNext();
    SnakePart *getPrev();
    Direction getDirectionFrom(SnakePart *);
};

#endif