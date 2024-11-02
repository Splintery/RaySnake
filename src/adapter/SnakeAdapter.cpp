#include <iostream>
#include "SnakeAdapter.hpp"
#include "../settings/Settings.hpp"

using namespace sf;

Adapter::~Adapter() {std::cout << "Destroyed adapter" << std::endl;}
Adapter::Adapter(Controller *ctlr): ctlr{ctlr} {}

SnakeAdapter::SnakeAdapter(Controller *ctlr): Adapter(ctlr) {}

Sprite *SnakeAdapter::getHeadTexture(SnakePart *part) {
    IntRect rect;
    Sprite *head = new Sprite();
    head->setTexture(ctlr->resourceManager->getTexture("snake_head"));

    switch (part->getDirection()) {
    case Direction::North:
        rect = IntRect(0, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::South:
        rect = IntRect(0, 0, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::East:
        rect = IntRect(0, TILE_SIZE * 3, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::West:
        rect = IntRect(0, TILE_SIZE, TILE_SIZE, TILE_SIZE);
        break;
    default:
        break;
    }
    head->setTextureRect(rect);
    return head;
}
Sprite *SnakeAdapter::getTailTexture(SnakePart *part) {
    IntRect rect;
    Sprite *tail = new Sprite();
    tail->setTexture(ctlr->resourceManager->getTexture("snake_tail"));

    switch (part->getDirection()) {
    case Direction::North:
        rect = IntRect(0, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::South:
        rect = IntRect(0, 0, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::East:
        rect = IntRect(0, TILE_SIZE * 3, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::West:
        rect = IntRect(0, TILE_SIZE, TILE_SIZE, TILE_SIZE);
        break;
    default:
        break;
    }
    tail->setTextureRect(rect);
    return tail;
}
Sprite *SnakeAdapter::getBodyTexture(SnakePart *part) {
    IntRect rect;
    Sprite *body = new Sprite();
    body->setTexture(ctlr->resourceManager->getTexture("snake_body"));

    switch (part->getDirection()) {
    case Direction::North:
        rect = IntRect(0, 0, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::South:
        rect = IntRect(0, 0, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::East:
        rect = IntRect(0, TILE_SIZE, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::West:
        rect = IntRect(0, TILE_SIZE, TILE_SIZE, TILE_SIZE);
        break;
    default:
        break;
    }
    body->setTextureRect(rect);
    return body;
}


Sprite *SnakeAdapter::getBentBodyTexture(SnakePart *part) {
    IntRect rect;
    Sprite *bent = new Sprite();
    bent->setTexture(ctlr->resourceManager->getTexture("snake_bent_body"));

    Direction toPrev = part->getDirectionFrom(part->getPrev());
    Direction toNext = part->getDirectionFrom(part->getNext());

    if (
        (toPrev == Direction::West && toNext == Direction::North)
        || (toPrev == Direction::North && toNext == Direction::West)
    ) {
        rect = IntRect(0, TILE_SIZE, TILE_SIZE, TILE_SIZE);
    } else if (
        (toPrev == Direction::South && toNext == Direction::West)
        || (toPrev == Direction::West && toNext == Direction::South)
    ) {
        rect = IntRect(0, 0, TILE_SIZE, TILE_SIZE);
    } else if (
        (toPrev == Direction::East && toNext == Direction::South)
        || (toPrev == Direction::South && toNext == Direction::East) 
    ) {
        rect = IntRect(0, TILE_SIZE * 3, TILE_SIZE, TILE_SIZE);
    } else {
        rect = IntRect(0, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE);
    }
    
    bent->setTextureRect(rect);
    return bent;
}


Sprite *SnakeAdapter::adaptPart(SnakePart *part) {
    if (part->getPrev() == nullptr) {
        return getHeadTexture(part);
    } else if (part->getNext() == nullptr) {
        return getTailTexture(part);
    } else {
        Vector2f prevPos = part->getPrev()->getPosition();
        Vector2f nextPos = part->getNext()->getPosition();
        if (prevPos.x == nextPos.x || prevPos.y == nextPos.y) {
            return getBodyTexture(part);
        } else {
            return getBentBodyTexture(part);
        }
    }
}

std::vector<Drawable *> SnakeAdapter::adapt(Adaptable *a) {
    Snake *snake = (Snake *) a;
    std::vector<Drawable *> adaptedSnake;
    SnakePart *currentPart = snake->getHead();

    while (currentPart != nullptr) {
        Sprite *part = adaptPart(currentPart);
        part->setPosition(
            currentPart->getPosition().x + ctlr->getWindowCenter().x,
            -currentPart->getPosition().y + ctlr->getWindowCenter().y
        );
        adaptedSnake.push_back(part);
        currentPart = currentPart->getNext();
    }
    return adaptedSnake;
}
