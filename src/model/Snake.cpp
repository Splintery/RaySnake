#include "Snake.hpp"

Snake::Snake(const Direction &dir, sf::Vector2f position): dir{dir} {
    head = new SnakePart(nullptr, nullptr, dir, position);
    tail = new SnakePart(head, nullptr, dir,  position - head->getNextPosition());
    head->addNext(tail);
    
    size = 2;
    grow(4);
}

void Snake::update() {

}

void Snake::grow(int n) {
    if (n > 0) {
        SnakePart *newTail = new SnakePart(tail, nullptr, tail->getDirection(), tail->getPosition() - tail->getNextPosition());
        tail->addNext(newTail);
        tail = newTail;
        size++;
        grow(n - 1);
    }
}

void Snake::move() {
    head->move();
}

void Snake::setDirection(const Direction &newDirection) {
    Direction currentDir = head->getDirection();

    switch (newDirection) {
    case Direction::North:
        if (currentDir != Direction::South) {head->setDirection(newDirection);}
        break;
    case Direction::South:
        if (currentDir != Direction::North) {head->setDirection(newDirection);}
        break;
    case Direction::East:
        if (currentDir != Direction::West) {head->setDirection(newDirection);}
        break;
    case Direction::West:
        if (currentDir != Direction::East) {head->setDirection(newDirection);}
        break;
    default:
        break;
    }
}

sf::Vector2f Snake::getHeadPosition() {
    return head->getPosition();
}

SnakePart *Snake::getHead() {
    return head;
}
SnakePart *Snake::getTail() {
    return tail;
}