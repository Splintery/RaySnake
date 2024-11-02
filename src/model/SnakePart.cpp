#include "SnakePart.hpp"
#include "Direction.hpp"


SnakePart::SnakePart(SnakePart *prev, SnakePart *next, Direction dir, Bound *bounds): prev{prev}, next{next}, dir{dir}, bounds{bounds} {
}

float SnakePart::size(float accumulator) {
    accumulator += (dir == Direction::North || dir == Direction::South) ? bounds->height() : bounds->width();

    if (next != nullptr) {
        return next->size(accumulator);
    } else {
        return accumulator;
    }
}

void SnakePart::growHead(float amount) {
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
void SnakePart::growTail(float amount) {
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

void SnakePart::removeNext() {
    delete(next);
    next = nullptr;
}
void SnakePart::removePrev() {
    delete(prev);
    prev = nullptr;
}
Direction SnakePart::getDirection() {
    return dir;
}
SnakePart *SnakePart::getNext() {
    return next;
}
SnakePart *SnakePart::getPrev() {
    return prev;
}
Bound *SnakePart::getBounds() {
    return bounds;
}

std::ostream &operator<<(std::ostream &out, const SnakePart &part) {
    return out;
}
