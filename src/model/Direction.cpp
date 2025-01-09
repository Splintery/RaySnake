#include <iostream>
#include "Direction.hpp"

using namespace sf;

Direction::Direction(Value v): value{v} {}
Direction::Direction(int i): value{static_cast<Value>(i)} {}
Direction Direction::invert() {
    return Direction(-(int)value);
}
Direction::operator Value() const { return value; }
bool Direction::operator==(Direction d) const { return value == d.value; }
bool Direction::operator==(Direction::Value v) const { return value == v; }
bool Direction::operator!=(Direction d) const { return value != d.value; }
bool Direction::operator!=(Direction::Value v) const { return value != v; }
Vector2f Direction::getVectorTowards(Direction d, sf::Vector2f p, float n) {
    switch (d) {
    case North:
        return p + Vector2f(0, n);
    case South:
        return p + Vector2f(0, -n);
    case East:
        return p + Vector2f(n, 0);
    case West:
        return p + Vector2f(-n, 0);
    default:
        return p;
    };
}
Bound *Direction::getBoundTowards(Direction d, Bound *b, float n) {
    return new Bound(getVectorTowards(d, b->topL, n), getVectorTowards(d, b->botR, n));
}

Bound *Direction::getStretchedBoundTowards(Direction d, Bound *b, float n) {
    return new Bound(
        (int)d.value > 0 ? getVectorTowards(d, b->topL, n) : b->topL,
        (int)d.value > 0 ? b->botR : getVectorTowards(d, b->botR, n) 
    );
}

std::ostream &operator<<(std::ostream &out, const Direction &d) {
    switch (d) {
    case Direction::North:
        out << "North";
        break;
    case Direction::South:
        out << "South";
        break;
    case Direction::East:
        out << "East";
        break;
    case Direction::West:
        out << "West";
        break;
    default:
        break;
    }
    return out;
}
// sf::Vector2f &operator*(const sf::Vector2f &l, const sf::Vector2f &r) {
//     sf::Vector2f o(
//         l.x * r.x,
//         l.y * r.y
//     );
//     return o;
// }
