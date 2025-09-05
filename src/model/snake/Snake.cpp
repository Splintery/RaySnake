#include <iostream>
#include "Snake.h"
#include "../tools/ObjectTracker.h"
#include "../tools/BoundFactory.h"

using namespace sf;

Adaptable::Adaptable() {}

Adaptable::~Adaptable() {}

void Snake::trimTail() {
    if (tail->getPrev() != nullptr) {
        tail = tail->getPrev();
        tail->removeNext();
    }
}
//TODO: the area of the bound created for the new head should be 0, having it be 1 makes it to "snappy", 0 would improve control
//? when it will be rendered, the head will stick out in front of the hit box a bit, giving player more time to react
void Snake::glueHead() {
    // BoundFactory fact = BoundFactory();
    // if (oldDir == Direction::North || oldDir == Direction::West) Bound b = fact.unitFromTopLeft(head->getBound(), width);
    // else Bound b = fact.unitFromBottomRight(head->getBound(), width);
    // Bound c = fact.getBoundTowards(b, newDir, width);
    
    // SnakePart *newHead = new SnakePart(nullptr, head, newDir, b);
    // head->addPrev(newHead);
    // head = newHead;
    // tail->grow(-1.0, false);
}

Snake::Snake(const Direction &dir, Vector2f position, float length) : newDir{dir}, oldDir{dir}, length{length} {
    Bound b = Bound(position, position + Vector2<float>(width, -width));
    head = new SnakePart(nullptr, nullptr, dir, b); //? When created the head is of size 0
    tail = head;
    grow(length); //? it then grows to the desired size
    ObjectTracker::addTo("Snake");
}

Snake::~Snake() {
    std::cout << "Destroying snake" << std::endl;
    SnakePart *tmp, *p = head;
    while (p != nullptr) {
        tmp = p;
        p = p->getNext();
        delete tmp;
    }
    ObjectTracker::removeFrom("Snake");
}

void Snake::update() {
    move(speed);
    length = head->size();
}
float Snake::size() {
    return length;
}
void Snake::grow(float amount) {
    tail->grow(amount, false);
}

void Snake::move(float amount) {    
    head->grow(amount, true);
    tail->grow(-amount, false);

    if (tail->size() <= width) {
        head->grow(tail->size(), true);
        trimTail();
    }

    if (newDir != oldDir) {
        glueHead();
    }
    oldDir = newDir;
    // std::cout << "Size of snake: " << head->totalSize() << std::endl;
}

void Snake::setDirection(const Direction &newDir) {
    if (int(newDir) != -int(oldDir)) {
        this->newDir = newDir;
    }
}
SnakePart *Snake::getHead() {
    return head;
}
SnakePart *Snake::getTail() {
    return tail;
}

Bound Snake::predictHeadPlacement(Direction newDir)
{
    if (newDir == oldDir)
    {
        
    }
    return Bound();
}

std::vector<Bound> Snake::getBounds()
{
    std::vector<Bound> res;
    SnakePart *curr = head;
    while (curr != nullptr) {
        res.push_back(curr->getBound());
        curr = curr->getNext();
    }
    return res;
}
std::vector<Direction> Snake::getDirections() {
    std::vector<Direction> res;
    SnakePart *curr = head;
    while (curr != nullptr) {
        res.push_back(curr->getDir());
        curr = curr->getNext();
    }
    return res;
}

std::ostream &operator<<(std::ostream &out, const Snake &snake) {
    SnakePart *currentPart = snake.head;
    while (currentPart != nullptr) {
        out << currentPart->getBound() << std::endl;
        currentPart = currentPart->getNext();
    }
    return out;
}