#include <iostream>
#include <cmath>
#include "SnakeAdapter.h"
#include "../settings/Settings.h"
#include "../view/AnimatedSprite.h"
#include "Adapter.h"

using namespace sf;

Adapter::~Adapter() { std::cout << "Destroyed adapter" << std::endl; }
Adapter::Adapter(Controller *ctrl, Adaptable *a): ctrl{ctrl}, adaptable{a} {}

Texture &SnakeAdapter::getCurvedBodyTexture(std::vector<Direction> &d, int i) {
    if (
        (d.at(i) == Direction::East && d.at(i - 1) == Direction::South)
        || (d.at(i) == Direction::North && d.at(i - 1) == Direction::West)
    ) {
        return ctrl->resourceManager->getBundle("snake_curved_body_bundle").at(0);
    } else if (
        (d.at(i) == Direction::South && d.at(i - 1) == Direction::West)
        || (d.at(i) == Direction::East && d.at(i - 1) == Direction::North)
    ) {
        return ctrl->resourceManager->getBundle("snake_curved_body_bundle").at(1);
    } else if (
        (d.at(i) == Direction::South && d.at(i - 1) == Direction::East)
        || (d.at(i) == Direction::West && d.at(i - 1) == Direction::North)
    ) {
        return ctrl->resourceManager->getBundle("snake_curved_body_bundle").at(2);
    } else {
        return ctrl->resourceManager->getBundle("snake_curved_body_bundle").at(3);
    }
}

float size(Bound *b, Direction d) {
    return (d == Direction::North || d == Direction::South) ? b->height() : b->width();
}

Texture &SnakeAdapter::findTexture(std::vector<Bound *> &b, std::vector<Direction> &d, int i, float j) {
    if (j == 0) {
        if (i == 0) {
            //with correct texture of head
            return ctrl->resourceManager->getBundle("snake_animated_head").at(d.at(i).toIndex());
        } else {
            return getCurvedBodyTexture(d, i);//with correct texture of curved body
        }
    } else if (size(b.at(i), d.at(i)) - j < 1.0 && i == b.size() - 1) {
        //with correct texture of tail
        return ctrl->resourceManager->getBundle("snake_tail_bundle").at(d.at(i).toIndex());
    } else {
        //with correct texture of body
        return ctrl->resourceManager->getBundle("snake_body_bundle").at(d.at(i).toIndex());
    }
}
// Sprite *SnakeAdapter::buildSprite(SnakePart *p, float i) {
//     if (i == 0 && p->getPrev() == nullptr) {
//         return new AnimatedSprite(findTexture(p, i), 7, 16, 7, 14);
//     } else {
//         return new Sprite(findTexture(p, i));
//     }
// }
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
Vector2f getStartPoint(Bound *b, Direction d) {
    return d == Direction::North || d == Direction::West ? b->topL : b->botR;
}
Vector2f mult(Vector2f v, Vector2f f) {
    return Vector2f(v.x * f.x, v.y * f.y);
}
Vector2f positionInWorld(Vector2f startPoint, Vector2f displacement, Vector2f windowCenter) {
    return mult(startPoint + displacement, Vector2f(16.0, -16.0)) + windowCenter;
}

SnakeAdapter::SnakeAdapter(Controller *ctrl, Adaptable *a) : Adapter(ctrl, a) {
    std::vector<Bound *> bounds = a->getBounds();
    std::vector<Direction> dirs = a->getDirections();
    for (int i = 0; i < bounds.size(); i++) {
        for (float j = 0.0; j < size(bounds.at(i), dirs.at(i)); j++) {
            if (size(bounds.at(i), dirs.at(i)) - j < 1.0) {
                j -= (1 - (size(bounds.at(i), dirs.at(i)) - j)) / 2.0;
            }
            Vector2f displacement = posInPart(dirs.at(i), j);
            Sprite *adaptedPart = new Sprite(findTexture(bounds, dirs, i, j));
            adaptedPart->setPosition(
                positionInWorld(
                    getStartPoint(bounds.at(i), dirs.at(i)), 
                    displacement, 
                    ctrl->getWindowCenter()
                )
            );
            sprites.push_back(adaptedPart);
        }
    }
}


void SnakeAdapter::update() {

}

void SnakeAdapter::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (sf::Drawable *d : sprites) {
        target.draw(*d, states);
    }
}
