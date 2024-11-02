#include "SnakeOptAdapter.hpp"
#include "../settings/Settings.hpp"

using namespace sf;

RectangleShape *SnakeOptAdapter::adaptPart(SnakeOptPart *part) {
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

SnakeOptAdapter::SnakeOptAdapter(Controller *ctlr) : Adapter(ctlr) {}

std::vector<Drawable *> SnakeOptAdapter::adapt(Adaptable *a) {
    SnakeOpt *snake = (SnakeOpt *) a;
    std::vector<Drawable *> adaptedSnake;

    SnakeOptPart *currentPart = snake->getHead();

    while (currentPart != nullptr) {
        adaptedSnake.push_back(adaptPart(currentPart));
        currentPart = currentPart->getNext();
    }

    return adaptedSnake;
}
