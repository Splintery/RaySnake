#include "SnakeOptPart.hpp"
#include "Direction.hpp"


SnakeOptPart::SnakeOptPart(SnakeOptPart *prev, SnakeOptPart *next, Direction dir, Bound *bounds): prev{prev}, next{next}, dir{dir}, bounds{bounds} {
}

float SnakeOptPart::size(float accumulator) {
    accumulator += (dir == Direction::North || dir == Direction::South) ? bounds->height() : bounds->width();

    if (next != nullptr) {
        return next->size(accumulator);
    } else {
        return accumulator;
    }
}

void SnakeOptPart::growHead(float amount) {
    switch (dir) {
    case Direction::North:
        bounds->topL.y += amount;
        break;
    case Direction::South:
        bounds->botR.y -= amount;
        break;
    case Direction::East:
        bounds->botR.x += amount;
        break;
    case Direction::West:
        bounds->topL.x -= amount;
        break;
    default:
        break;
    }
}
void SnakeOptPart::growTail(float amount) {
    switch (dir) {
    case Direction::North:
        bounds->botR.y -= amount;
        break;
    case Direction::South:
        bounds->topL.y += amount;
        break;
    case Direction::East:
        bounds->topL.x -= amount;
        break;
    case Direction::West:
        bounds->botR.x += amount;
        break;
    default:
        break;
    }
}

void SnakeOptPart::addNext(SnakeOptPart *newPart) {
    if (next != nullptr) {
        next->prev = newPart;
    }
    newPart->prev = this;
    newPart->next = next;
    next = newPart;
}
void SnakeOptPart::addPrev(SnakeOptPart *newPart) {
    if (prev != nullptr) {
        prev->next = newPart;
    }
    newPart->prev = prev;
    newPart->next = this;
    prev = newPart;
}

void SnakeOptPart::removeNext() {
    delete(next);
    next = nullptr;
}
void SnakeOptPart::removePrev() {
    delete(prev);
    prev = nullptr;
}
Direction SnakeOptPart::getDirection() {
    return dir;
}
SnakeOptPart *SnakeOptPart::getNext() {
    return next;
}
SnakeOptPart *SnakeOptPart::getPrev() {
    return prev;
}
Bound *SnakeOptPart::getBounds() {
    return bounds;
}

std::ostream &operator<<(std::ostream &out, const SnakeOptPart &part) {
    return out;
}
