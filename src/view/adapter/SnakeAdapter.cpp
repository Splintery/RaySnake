#include "SnakeAdapter.hpp"
#include "../../settings/Settings.hpp"

SnakeAdapter::SnakeAdapter(Controller *controller): controller{controller} {}

sf::Sprite SnakeAdapter::getHeadTexture(SnakePart *part) {
    sf::IntRect rect;
    sf::Sprite head;
    head.setTexture(controller->resourceManager->getTexture("snake_head"));

    switch (part->getDirection()) {
    case Direction::North:
        rect = sf::IntRect(0, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::South:
        rect = sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::East:
        rect = sf::IntRect(0, TILE_SIZE * 3, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::West:
        rect = sf::IntRect(0, TILE_SIZE, TILE_SIZE, TILE_SIZE);
        break;
    default:
        break;
    }
    head.setTextureRect(rect);
    return head;
}
sf::Sprite SnakeAdapter::getTailTexture(SnakePart *part) {
    sf::IntRect rect;
    sf::Sprite tail;
    tail.setTexture(controller->resourceManager->getTexture("snake_tail"));

    switch (part->getDirection()) {
    case Direction::North:
        rect = sf::IntRect(0, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::South:
        rect = sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::East:
        rect = sf::IntRect(0, TILE_SIZE * 3, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::West:
        rect = sf::IntRect(0, TILE_SIZE, TILE_SIZE, TILE_SIZE);
        break;
    default:
        break;
    }
    tail.setTextureRect(rect);
    return tail;
}
sf::Sprite SnakeAdapter::getBodyTexture(SnakePart *part) {
    sf::IntRect rect;
    sf::Sprite body;
    body.setTexture(controller->resourceManager->getTexture("snake_body"));

    switch (part->getDirection()) {
    case Direction::North:
        rect = sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::South:
        rect = sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::East:
        rect = sf::IntRect(0, TILE_SIZE, TILE_SIZE, TILE_SIZE);
        break;
    case Direction::West:
        rect = sf::IntRect(0, TILE_SIZE, TILE_SIZE, TILE_SIZE);
        break;
    default:
        break;
    }
    body.setTextureRect(rect);
    return body;
}


sf::Sprite SnakeAdapter::getBentBodyTexture(SnakePart *part) {
    sf::IntRect rect;
    sf::Sprite bent;
    bent.setTexture(controller->resourceManager->getTexture("snake_bent_body"));

    Direction toPrev = part->getDirectionFrom(part->getPrev());
    Direction toNext = part->getDirectionFrom(part->getNext());

    if (
        (toPrev == Direction::West && toNext == Direction::North)
        || (toPrev == Direction::North && toNext == Direction::West)
    ) {
        rect = sf::IntRect(0, TILE_SIZE, TILE_SIZE, TILE_SIZE);
    } else if (
        (toPrev == Direction::South && toNext == Direction::West)
        || (toPrev == Direction::West && toNext == Direction::South)
    ) {
        rect = sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE);
    } else if (
        (toPrev == Direction::East && toNext == Direction::South)
        || (toPrev == Direction::South && toNext == Direction::East) 
    ) {
        rect = sf::IntRect(0, TILE_SIZE * 3, TILE_SIZE, TILE_SIZE);
    } else {
        rect = sf::IntRect(0, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE);
    }
    
    bent.setTextureRect(rect);
    return bent;
}


sf::Sprite SnakeAdapter::adaptPart(SnakePart *part) {
    if (part->getPrev() == nullptr) {
        return getHeadTexture(part);
    } else if (part->getNext() == nullptr) {
        return getTailTexture(part);
    } else {
        sf::Vector2f prevPos = part->getPrev()->getPosition();
        sf::Vector2f nextPos = part->getNext()->getPosition();
        if (prevPos.x == nextPos.x || prevPos.y == nextPos.y) {
            return getBodyTexture(part);
        } else {
            return getBentBodyTexture(part);
        }
    }
}

std::list<sf::Sprite> SnakeAdapter::adaptSnake(Snake *snake) {
    std::list<sf::Sprite> adaptedSnake;
    SnakePart *currentPart = snake->getHead();

    while (currentPart != nullptr) {
        sf::Sprite part = adaptPart(currentPart);
        part.setPosition(
            currentPart->getPosition().x * TILE_SIZE + controller->getWindowCenter().x,
            -currentPart->getPosition().y * TILE_SIZE + controller->getWindowCenter().y
        );
        adaptedSnake.push_back(part);
        currentPart = currentPart->getNext();
    }
    return adaptedSnake;
}
