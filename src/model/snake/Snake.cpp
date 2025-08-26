#include <iostream>
#include "Snake.h"

using namespace sf;

Adaptable::Adaptable() {}

Adaptable::~Adaptable() {}

void Snake::trimTail() {
    if (tail->getPrev() != nullptr) {
        tail = tail->getPrev();
        tail->removeNext();
    }
}

void Snake::glueHead() {
    Bound *unit = new Bound(head->getBound(), oldDir == Direction::North || oldDir == Direction::West);
    Bound *tmp = Direction::getBoundTowards(
        newDir,
        unit,
        1.0f
    );
    
    SnakePart *newHead = new SnakePart(nullptr, head, newDir, tmp);
    head->addPrev(newHead);
    head = newHead;
    tail->grow(-1.0, false);
}

Snake::Snake(const Direction &dir, Vector2f position, float length) : newDir{dir}, oldDir{dir} {
    std::cout << "Creating snake" << std::endl;
    Bound *b;
    if (dir == Direction::North || dir == Direction::South) {
        b = new Bound(position, position + Vector2f(1, -2));
    } else {
        b = new Bound(position, position + Vector2f(2, -1));
    }
    head = new SnakePart(nullptr, nullptr, dir, b);
    tail = head;
    if (head->size() < length) {
        grow(length - head->size());
    }
    this->length = head->size();
}

Snake::~Snake() {
    std::cout << "Destroying snake" << std::endl;
    SnakePart *tmp, *p = head;
    while (p != nullptr) {
        tmp = p;
        p = p->getNext();
        delete tmp;
    }
}

void Snake::update() {
    move(0.10f);
    length = head->size();
}
float Snake::size() {
    return length;
}
void Snake::grow(float amount) {
    tail->grow(amount, false);
}

void Snake::move(float amount) {    
    if (newDir != oldDir) {
        glueHead();
    }

    head->grow(amount, true);
    
    tail->grow(-amount, false);

    if (tail->size() <= 1.0) {
        head->grow(tail->size(), true);
        trimTail();
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

std::vector<Bound *> Snake::getBounds() {
    std::vector<Bound *> res;
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
        out << *(currentPart->getBound()) << std::endl;
        currentPart = currentPart->getNext();
    }
    return out;
}