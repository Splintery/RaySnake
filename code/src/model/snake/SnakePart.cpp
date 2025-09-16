#include <iostream>
#include "SnakePart.h"
#include "../tools/ObjectTracker.h"
#include "../tools/BoundFactory.h"

SnakePart::SnakePart(SnakePart *prev, SnakePart *next, Direction dir, Bound bounds): prev{prev}, next{next}, dir{dir}, bounds{bounds}
{
    ObjectTracker::addTo("SnakePart");
}

SnakePart::~SnakePart()
{
    std::cout << "Destroying snakepart" << std::endl;
    ObjectTracker::removeFrom("SnakePart");
}

float SnakePart::size() {
    return (dir == Direction::North || dir == Direction::South) ? bounds.height() : bounds.width();
}

float SnakePart::totalSize(float accumulator)
{
    accumulator += size();

    if (next != nullptr) {
        return next->totalSize(accumulator);
    } else {
        return accumulator;
    }
}

void SnakePart::grow(float amount, bool head)
{
    BoundFactory factory = BoundFactory();
    this->bounds = factory.stretchTowards(bounds, head ? dir : dir.invert(), amount);
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
Direction SnakePart::getDir() {
    return dir;
}
SnakePart *SnakePart::getNext() {
    return next;
}
SnakePart *SnakePart::getPrev() {
    return prev;
}
Bound SnakePart::getBound() {
    return bounds;
}

std::ostream &operator<<(std::ostream &out, const SnakePart &part) {
    out << "part{" << part.bounds << "}";
    return out;
}
