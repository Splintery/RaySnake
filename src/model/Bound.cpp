#include "Bound.hpp"
#include <cmath>


Bound::Bound(sf::Vector2f topL, sf::Vector2f botR): topL{topL}, botR{botR} {}
Bound::Bound(float x1, float y1, float x2, float y2): Bound(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2)) {}
Bound::Bound(): Bound(0.0f, 0.0f, 0.0f, 0.0f) {}

float abs(float val) {
    if (val > 0) {
        return val;
    } else {
        return -val;
    }
}

float Bound::width() const {
    return abs(topL.x - botR.x);
}

float Bound::height() const {
    return abs(topL.y - botR.y);
}

void Bound::move(sf::Vector2f p) {
    topL += p;
    botR += p;
}

std::ostream &operator<<(std::ostream &out, const Bound &bound) {
    out << "TopLeft[" << bound.topL.x << "; " << bound.topL.y
    << "]-BotRight[" << bound.botR.x << "; " << bound.botR.y
    << "]-Width[" << bound.width()
    << "]-Height[" << bound.height() << "]" << std::endl;

    return out;
}
