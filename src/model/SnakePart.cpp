#include "SnakePart.hpp"
#include "Direction.hpp"


SnakePart::SnakePart(SnakePart *prev, SnakePart *next, Direction dir, sf::Vector2f position): prev{prev}, next{next}, dir{dir}, position{position} {
}

void SnakePart::move() {
    // printf("OldPos[%f, %f]", position.x, position.y);
    position += getNextPosition();
    // printf("-> NewPos[%f, %f]\n", position.x, position.y);
    
    if (next != nullptr) {
        next->move();
    }
    if (prev != nullptr) {
        setDirection(prev->getDirection());
    }
}

void SnakePart::addNext(SnakePart *newPart) {
    if (next != nullptr) {
        next->prev = newPart;
    }
    newPart->prev = this;
    newPart->next = next;
    next = newPart;
}
void SnakePart::addPrev(SnakePart *newPart) {
    if (prev != nullptr) {
        prev->next = newPart;
    }
    newPart->prev = prev;
    newPart->next = this;
    prev = newPart;
}

void SnakePart::setDirection(const Direction &newDirection) {
    dir = newDirection;
}
Direction SnakePart::getDirection() {
    return dir;
}
sf::Vector2f SnakePart::getPosition() {
    return position;
}

sf::Vector2f SnakePart::getNextPosition() {
    sf::Vector2f nextPos(0.0, 0.0);
    switch (dir)
    {
    case Direction::North:
        nextPos.y = 1;
        break;
    case Direction::South:
        nextPos.y = -1;
        break;
    case Direction::East:
        nextPos.x = 1;
        break;
    case Direction::West:
        nextPos.x = -1;
        break;
    default:
        break;
    }
    return nextPos;
}

// sf::Sprite SnakePart::getSprite() {
//     return sprite;
// }

SnakePart *SnakePart::getNext() {
    return next;
}

SnakePart *SnakePart::getPrev() {
    return prev;
}

Direction SnakePart::getDirectionFrom(SnakePart *from) {
    sf::Vector2f difference = position - from->getPosition();

    if (difference == sf::Vector2f(1, 0)) {
        return Direction::West;
    } else if (difference == sf::Vector2f(-1, 0)) {
        return Direction::East;
    } else if (difference == sf::Vector2f(0, 1)) {
        return Direction::South;
    } else {
        return Direction::North;
    }
}
