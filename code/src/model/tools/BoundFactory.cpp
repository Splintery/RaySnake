#include "BoundFactory.h"

Bound BoundFactory::unitFromTopLeft(Bound b, float width)
{
    return Bound(b.topL, b.topL + sf::Vector2<float>(width, -width));
}
Bound BoundFactory::unitFromBottomRight(Bound b, float width)
{
    return Bound(b.botR + sf::Vector2<float>(-width, width), b.botR);
}
Bound BoundFactory::stretchTowards(Bound b, Direction d, float amount)
{
    return Bound( //? (int)d > 0 -> stretching towards North or West
    (int)d > 0 ? Direction::getVectorTowards(d, b.topL, amount) : b.topL,
    (int)d > 0 ? b.botR : Direction::getVectorTowards(d, b.botR, amount));
}
Bound BoundFactory::getBoundTowards(Bound b, Direction d, float amount)
{
    return Bound(Direction::getVectorTowards(d, b.topL, amount), Direction::getVectorTowards(d, b.botR, amount));
}