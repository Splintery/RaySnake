#ifndef BOUNDFACTORY_HPP
#define BOUNDFACTORY_HPP

#include "Bound.h"
#include "Direction.h"
#include <SFML/System/Vector2.hpp>

class BoundFactory
{
public:
    Bound rebuildFromTopLeft(Bound b, float width)
    {
        return Bound(b.topL, b.topL + sf::Vector2<float>(width, -width));
    }
    Bound rebuildFromBottomRight(Bound b, float width)
    {
        return Bound(b.botR + sf::Vector2<float>(-width, width), b.botR);
    }
    Bound stretchTowards(Bound b, Direction d, float amount)
    {
        return Bound( //? (int)d > 0 -> stretching towards North or West
        (int)d > 0 ? Direction::getVectorTowards(d, b.topL, amount) : b.topL,
        (int)d > 0 ? b.botR : Direction::getVectorTowards(d, b.botR, amount));
    }
};
#endif