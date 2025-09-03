#ifndef BOUNDFACTORY_HPP
#define BOUNDFACTORY_HPP

#include "Bound.h"
#include "Direction.h"
#include <SFML/System/Vector2.hpp>

class BoundFactory
{
public:
    Bound unitFromTopLeft(Bound, float);
    Bound unitFromBottomRight(Bound, float);
    Bound stretchTowards(Bound, Direction, float);
    Bound getBoundTowards(Bound, Direction, float);
};
#endif