#include <iostream>
#include "Bound.hpp"

using namespace sf;

float abs(float val) {
    if (val > 0) {
        return val;
    } else {
        return -val;
    }
}

Bound::Bound(Vector2f topL, Vector2f botR): topL{topL}, botR{botR} {}
Bound::Bound(float x1, float y1, float x2, float y2): Bound(Vector2f(x1, y1), Vector2f(x2, y2)) {}
Bound::Bound(): Bound(0.0, 0.0, 0.0, 0.0) {}
Bound::~Bound() {
    // std::cout << "Deleting Bound" << std::endl;
}
Bound::Bound(const Bound &) {
    std::cout << "Copyng Bound" << std::endl;
}
Bound::Bound(Bound *b, bool fromTl) : 
Bound(
    fromTl ? b->topL : b->botR + Vector2f(-1, 1),
    fromTl ? b->topL + Vector2f(1, -1) : b->botR
)
{}

float Bound::width() const
{
    return abs(topL.x - botR.x);
}

float Bound::height() const {
    return abs(topL.y - botR.y);
}

bool Bound::contains(float x, float y) {
    return x >= topL.x && x < botR.x && y <= topL.y && y > botR.y;
}

bool Bound::contains(Vector2f p) {
    return contains(p.x, p.y);
}

std::ostream &operator<<(std::ostream &out, const Bound &bound) {
    out << "TopLeft[" << bound.topL.x << "; " << bound.topL.y
    << "]-BotRight[" << bound.botR.x << "; " << bound.botR.y
    << "]-Width[" << bound.width()
    << "]-Height[" << bound.height() << "]";

    return out;
}
