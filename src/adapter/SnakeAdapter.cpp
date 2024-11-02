#include <iostream>
#include "SnakeAdapter.hpp"
#include "../settings/Settings.hpp"

using namespace sf;

Adapter::~Adapter() {std::cout << "Destroyed adapter" << std::endl;}
Adapter::Adapter(Controller *ctlr): ctlr{ctlr} {}

RectangleShape *SnakeAdapter::adaptPart(SnakePart *part) {
    Bound *b = part->getBounds();
    RectangleShape *res = new RectangleShape(Vector2f(b->width(), b->height()));
    res->setPosition(
        Vector2f(b->topL.x, -b->topL.y) + Vector2f(ctlr->getWindowCenter())
    );
    if (part->getPrev() == nullptr) {
        res->setFillColor(Color::Green);
    } else if (part->getNext() == nullptr) {
        res->setFillColor(Color::Red);
    } else {
        res->setFillColor(Color::White);
    }

    return res;
}

SnakeAdapter::SnakeAdapter(Controller *ctlr) : Adapter(ctlr) {}

std::vector<Drawable *> SnakeAdapter::adapt(Adaptable *a) {
    Snake *snake = (Snake *) a;
    std::vector<Drawable *> adaptedSnake;

    SnakePart *currentPart = snake->getHead();

    while (currentPart != nullptr) {
        adaptedSnake.push_back(adaptPart(currentPart));
        currentPart = currentPart->getNext();
    }

    return adaptedSnake;
}
