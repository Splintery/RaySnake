#include <iostream>
#include <cmath>
#include "SnakeAdapter.hpp"
#include "../settings/Settings.hpp"
#include "Adapter.hpp"

using namespace sf;

Adapter::~Adapter() { std::cout << "Destroyed adapter" << std::endl; }
Adapter::Adapter(Controller *ctrl): ctrl{ctrl} {}
SnakeAdapter::SnakeAdapter(Controller *ctrl) : Adapter(ctrl) {}

//TODO: Factorize these getBlablaTexture methods
Texture &SnakeAdapter::getHeadTexture(SnakePart *part) {
    return ctrl->resourceManager->getBundle("snake_tail_bundle").at(part->getDir().toIndex());
}
Texture &SnakeAdapter::getCurvedBodyTexture(SnakePart *part) {
    if (
        (part->getDir() == Direction::East && part->getPrev()->getDir() == Direction::South)
        || (part->getDir() == Direction::North && part->getPrev()->getDir() == Direction::West)
    ) {
        return ctrl->resourceManager->getBundle("snake_curved_body_bundle").at(0);
    } else if (
        (part->getDir() == Direction::South && part->getPrev()->getDir() == Direction::West)
        || (part->getDir() == Direction::East && part->getPrev()->getDir() == Direction::North)
    ) {
        return ctrl->resourceManager->getBundle("snake_curved_body_bundle").at(1);
    } else if (
        (part->getDir() == Direction::South && part->getPrev()->getDir() == Direction::East)
        || (part->getDir() == Direction::West && part->getPrev()->getDir() == Direction::North)
    ) {
        return ctrl->resourceManager->getBundle("snake_curved_body_bundle").at(2);
    } else {
        return ctrl->resourceManager->getBundle("snake_curved_body_bundle").at(3);
    }
}
Texture &SnakeAdapter::getBodyTexture(SnakePart *part) {
    return ctrl->resourceManager->getBundle("snake_body_bundle").at(part->getDir().toIndex());
}
Texture &SnakeAdapter::getTailTexture(SnakePart *part) {
    return ctrl->resourceManager->getBundle("snake_tail_bundle").at(part->getDir().toIndex());
}
Texture &SnakeAdapter::findTexture(SnakePart *p, float i) {
    if (i == 0) {
        if (p->getPrev() == nullptr) {
           return getHeadTexture(p);//with correct texture of head
        } else {
            return getCurvedBodyTexture(p);//with correct texture of curved body
        }
    } else if (p->size() - i < 1.0 && p->getNext() == nullptr) {
        return getTailTexture(p);//with correct texture of tail
    } else {
        return getBodyTexture(p);//with correct texture of body
    }
}
Vector2f posInPart(Direction d, float i) {
    switch (d) {
        case Direction::North: return Vector2f(0, -i);
        case Direction::South: return Vector2f(-1, i+1);
        case Direction::East: return Vector2f(-(i+1), 1);
        case Direction::West: return Vector2f(i, 0);
    default:
        return Vector2f();
    }
}
Vector2f getStartPoint(SnakePart *p) {
    return p->getDir() == Direction::North || p->getDir() == Direction::West ? p->getBounds()->topL : p->getBounds()->botR;
}
Vector2f mult(Vector2f v, Vector2f f) {
    return Vector2f(v.x * f.x, v.y * f.y);
}
Vector2f positionInWorld(SnakePart *p, Vector2f displacement, Vector2f windowCenter) {
    return mult(getStartPoint(p) + displacement, Vector2f(16.0, -16.0)) + windowCenter;
}

std::vector<Drawable *> SnakeAdapter::adapt(Adaptable *a)
{
    Snake *snake = (Snake *) a;
    std::vector<Drawable * > adaptedSnake;
    int tmp = 0;
    for (SnakePart *part = snake->getHead(); part != nullptr; part = part->getNext()) {
        int sum = 0;
        bool ab = false;
        for (float i = 0.0; i < part->size(); i++) {
            //TODO: Take into account that the last iteration of this loop needs special displacement
            //when size is 2.4: 3 sprites are required but the last must be set to overlap
            //the previous one when its length will make it pertrude from the snake
            if (part->size() - i < 1.0) {
                i -= (1 - (part->size() - i)) / 2.0;
                ab = true;
            }
            Vector2f displacement = posInPart(part->getDir(), i);
            Sprite *adaptedPart = new Sprite(findTexture(part, i));
            if (i == 0) {
                adaptedPart->setColor(Color::Red);
            } else if (ab) {
                adaptedPart->setColor(Color::Green);
            }
            adaptedPart->setPosition(positionInWorld(part, displacement, ctrl->getWindowCenter()));
            adaptedSnake.push_back(adaptedPart);
            if (part->size() - i < 1.0) {
                tmp++;
            }
            sum++;
        }
        Text *label = new Text(std::to_string(part->size()) + ": " + std::to_string(sum), ctrl->resourceManager->getFont("minecraft"), 32);
        label->setScale(0.1, 0.1);
        label->setFillColor(Color::Red);
        label->setPosition(positionInWorld(part, Vector2f(), ctrl->getWindowCenter()));
        adaptedSnake.push_back(label);
    }
    printf("dernier morceau, %d\n", tmp);
    return adaptedSnake;
}
