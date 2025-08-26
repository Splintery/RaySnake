#include <iostream>
#include "Direction.h"

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
int Direction::toIndex() const {
    switch (value) {
    case North:
        return 0;
    case South:
        return 1;
    case East:
        return 2;
    case West:
        return 3;
    default:
        return -1;
    }
}
Vector2<float> Direction::getVectorTowards(Direction d, sf::Vector2<float> p, float n)
{
    switch (d) {
    case North:
        return p + Vector2<float>(0, n);
    case South:
        return p + Vector2<float>(0, -n);
    case East:
        return p + Vector2<float>(n, 0);
    case West:
        return p + Vector2<float>(-n, 0);
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
