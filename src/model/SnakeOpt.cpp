#include <iostream>
#include "SnakeOpt.hpp"
#include "Bound.hpp"

using namespace sf;

void SnakeOpt::trimTail() {
    if (tail->getPrev() != nullptr) {
        tail = tail->getPrev();
        tail->removeNext();
    }
}
Bound *counterClockwise(Bound *b, int sumDir) {
    switch (sumDir) {
        case 1:
            return new Bound(b->botR + Vector2f(0, 10), b->botR + Vector2f(10, 0));
        case -1:
            return new Bound(b->topL + Vector2f(-10, 0), b->topL + Vector2f(0, -10));
        case -3:
            return new Bound(b->topL + Vector2f(0, -10), b->topL + Vector2f(10, -20));
        default:
            return new Bound(b->botR + Vector2f(-10, 20), b->botR + Vector2f(0, 10));
    }
}
Bound *clockwise(Bound *b, int sumDir) {
    switch (sumDir) {
        case 1:
            return new Bound(b->botR + Vector2f(-10, 0), b->botR + Vector2f(0, -10));
        case -1:
            return new Bound(b->topL + Vector2f(0, 10), b->topL + Vector2f(10, 0));
        case -3:
            return new Bound(b->botR + Vector2f(-20, 10), b->botR + Vector2f(-10, 0));
        default:
            return new Bound(b->topL + Vector2f(0, 0), b->topL + Vector2f(20, -10));
    }
}
Bound *decideOrientation(Direction oldir, Direction newDir, Bound *hb) {
    if ((oldir == Direction::North && newDir == Direction::East)
    || (oldir == Direction::South && newDir == Direction::West)
    || (oldir == Direction::East && newDir == Direction::South)
    || (oldir == Direction::West && newDir == Direction::North)) {
        return clockwise(hb, (int)oldir + (int)newDir);
    } else {
        return counterClockwise(hb, (int)oldir + (int)newDir);
    }
}

void SnakeOpt::glueHead() {
    Bound *b = decideOrientation(oldDir, dir, head->getBounds());
    SnakeOptPart *newHead = new SnakeOptPart(nullptr, head, dir, b);
    head->addPrev(newHead);
    head = newHead;
    tail->growTail(-10.0);
}

SnakeOpt::SnakeOpt(const Direction &dir, Vector2f position, float length) : dir{dir}, oldDir{dir} {
    Bound *b;
    if (dir == Direction::North || dir == Direction::South) {
        b = new Bound(position, position + Vector2f(10, -20));
    } else {
        b = new Bound(position, position + Vector2f(20, -10));
    }
    head = new SnakeOptPart(nullptr, nullptr, dir, b);
    tail = head;
    this->length = head->size();
}

void SnakeOpt::update() {
    length = head->size();
}
float SnakeOpt::size() {
    return length;
}
void SnakeOpt::grow(float amount) {
    tail->growTail(amount);
}

void SnakeOpt::move(float amount) {
    if (dir != oldDir) {
        glueHead();
    }

    head->growHead(amount);
    
    tail->growTail(-amount);

    if (tail->size() <= 10.0) {
        head->growHead(tail->size());
        trimTail();
    }
    oldDir = dir;
}

void SnakeOpt::setDirection(const Direction &newDir) {
    printf("%d\n", (int)newDir);
    if (int(newDir) != -int(oldDir)) {
        dir = newDir;
    }
}
SnakeOptPart *SnakeOpt::getHead() {
    return head;
}
SnakeOptPart *SnakeOpt::getTail() {
    return tail;
}

std::ostream &operator<<(std::ostream &out, const SnakeOpt &snake) {
    SnakeOptPart *currentPart = snake.head;
    while (currentPart != nullptr) {
        out << *(currentPart->getBounds()) << std::endl;
        currentPart = currentPart->getNext();
    }
    return out;
}